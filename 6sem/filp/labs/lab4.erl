-module(tasks).
-export([main/1, star/2, parent_children/1, send_to_child/2, stop/0, par_foreach/3]).

%%% ЗАДАНИЕ 1: ЗВЕЗДООБРАЗНАЯ ТОПОЛОГИЯ ПРОЦЕССОВ %%%
% Функция star(N, M) создает N+1 процессов (1 центральный и N крайних)
% N - количество крайних процессов, M - количество итераций обмена сообщениями

star(N, M) when is_integer(N), N >= 0, is_integer(M), M >= 0 ->
    io:format("Current process is ~p~n", [self()]),
    Center = spawn_link(fun() -> center_loop(N) end), % Создаем центральный процесс
    io:format("Created center process ~p~n", [Center]),
    % Создаем N крайних процессов, каждый с ссылкой на центральный процесс
    Pids = [spawn_link(fun() -> edge_loop(Center) end) || _ <- lists:seq(1, N)],
    % Отправляем центральному процессу сообщение с PIDами крайних процессов и количеством итераций
    Center ! {start, Pids, M}.

% Главный цикл центрального процесса
center_loop(N) ->
    receive
        {start, Pids, CurrentM} -> % Получаем начальное сообщение
            io:format("Center ~p starting iteration ~p~n", [self(), CurrentM]),
            if 
                CurrentM > 0 -> % Если остались итерации
                    broadcast(Pids, CurrentM), % Рассылаем сообщения
                    wait_responses(N, CurrentM, Pids); % Ждем ответы
                true -> % Если итерации закончились
                    io:format("Center ~p finished~n", [self()]),
                    [Pid ! stop || Pid <- Pids], % Останавливаем все крайние процессы
                    ok
            end
    end.

% Рассылка сообщений всем дочерним процессам
broadcast([], _) -> ok;
broadcast([Pid | Rest], Msg) -> 
    Pid ! {msg, self(), Msg},
    broadcast(Rest, Msg).

% Ожидание ответов от дочерних процессов
wait_responses(0, CurrentM, Pids) -> % Все ответы получены
    io:format("Center received all responses, starting next iteration~n"),
    % Запускаем следующую итерацию с уменьшенным счетчиком
    self() ! {start, Pids, CurrentM - 1},
    center_loop(length(Pids));
wait_responses(N, CurrentM, Pids) -> % Ожидаем N ответов
    receive
        {done, Pid} -> % Получаем ответ от процесса
            io:format("Center received response from ~p (~p left)~n", [Pid, N - 1]),
            wait_responses(N - 1, CurrentM, Pids) % Уменьшаем счетчик ожидаемых ответов
    end.

% Цикл крайнего процесса
edge_loop(Center) ->
    receive
        {msg, Center, Msg} -> % Получаем сообщение от центрального процесса
            io:format("Edge ~p received message ~p~n", [self(), Msg]),
            Center ! {done, self()}, % Отправляем подтверждение
            edge_loop(Center);
        stop ->
            io:format("Edge ~p stopping~n", [self()]),
            ok
    end.

%%% ЗАДАНИЕ 2: РОДИТЕЛЬ И ДОЧЕРНИЕ ПРОЦЕССЫ %%%
% Создает родительский процесс и N дочерних

parent_children(N) when is_integer(N), N >= 0 ->
    Parent = spawn(fun() -> parent_loop(N, []) end), 
    register(parent, Parent).

% Главный цикл родительского процесса
parent_loop(N, Children) ->
    process_flag(trap_exit, true), % Включаем перехват сообщений о завершении
    NewChildren = case length(Children) of
        N -> Children; % Если уже N процессов, оставляем как есть
        _ -> 
            Child = spawn_link(fun() -> child_loop() end), % Создаем новый дочерний процесс
            Children ++ [Child] 
    end,
    receive
        {send_to, I, Msg} when I >= 1, I =< N ->
            case I =< length(NewChildren) of
                true -> 
                    lists:nth(I, NewChildren) ! Msg, % Отправляем сообщение
                    parent_loop(N, NewChildren);
                false ->
                    parent_loop(N, NewChildren)
            end;
        stop ->
            io:format("Parent stopping all children~n"),
            [Child ! stop || Child <- NewChildren], % Останавливаем все дочерние процессы
            ok;
        {'EXIT', Pid, Reason} ->
            io:format("Child ~p crashed (~p), restarting~n", [Pid, Reason]),
            % Создаем новый процесс вместо упавшего
            NewChild = spawn_link(fun() -> child_loop() end),
            % Обновляем список процессов
            UpdatedChildren = lists:map(
                fun(C) when C == Pid -> NewChild;
                   (C) -> C
                end, NewChildren),
            parent_loop(N, UpdatedChildren)
    end.

% Цикл дочернего процесса
child_loop() ->
    receive
        stop ->
            io:format("Child ~p stopping~n", [self()]),
            ok;
        die ->
            io:format("Child ~p dying~n", [self()]),
            exit(crash);
        Msg ->
            io:format("Child ~p received: ~p~n", [self(), Msg]), 
            child_loop()
    end.

% Отправка сообщения дочернему процессу по индексу
send_to_child(I, Msg) when is_integer(I), I >= 1 ->
    parent ! {send_to, I, Msg}.

% Остановка родительского и всех дочерних процессов
stop() ->
    parent ! stop.

%%% ЗАДАНИЕ 3: ПАРАЛЛЕЛЬНЫЙ FOREACH %%%
% Параллельный аналог lists:foreach/2
% F - функция для применения, List - список элементов, Options - параметры

par_foreach(F, List, Options) when is_function(F, 1), is_list(List), is_list(Options) ->
    Processes = proplists:get_value(processes, Options, length(List)), % Количество процессов
    SublistSize = proplists:get_value(sublist_size, Options, 1), % Размер подсписка
    Timeout = proplists:get_value(timeout, Options, infinity), % Таймаут
    
    % Разбиваем список на подсписки
    Sublists = split_list(List, SublistSize),
    % Определяем реальное количество процессов (не больше чем подсписков)
    ActualProcesses = min(Processes, length(Sublists)),
    
    % Создаем мониторируемые процессы для обработки подсписков
    Pids = [spawn_monitor(fun() -> foreach_worker(F, Sublist) end)
           || Sublist <- lists:sublist(Sublists, ActualProcesses)],
    % Ожидаем завершения процессов
    wait_for_results(Pids, Timeout, length(Pids)).

% Разделение списка на подсписки указанного размера
split_list(List, Size) when Size > 0 ->
    split_list_helper(List, Size, []).

split_list_helper([], _, Acc) -> lists:reverse(Acc); 
split_list_helper(List, Size, Acc) ->
    case length(List) > Size of
        true ->
            {Sublist, Rest} = lists:split(Size, List),
            split_list_helper(Rest, Size, [Sublist | Acc]);
        false ->
            lists:reverse([List | Acc])
    end.

% Рабочая функция для каждого процесса
foreach_worker(F, Sublist) ->
    lists:foreach(F, Sublist). % Применяем F к каждому элементу подсписка

% Ожидание завершения всех рабочих процессов
wait_for_results(Pids, Timeout, Remaining) when Remaining > 0 ->
    receive
        {'DOWN', _Ref, process, Pid, normal} ->
            wait_for_results(lists:keydelete(Pid, 2, Pids), Timeout, Remaining - 1);
        {'DOWN', _Ref, process, Pid, Reason} ->
            io:format("Worker ~p failed: ~p~n", [Pid, Reason]),
            wait_for_results(lists:keydelete(Pid, 2, Pids), Timeout, Remaining - 1)
    after Timeout ->
        [exit(Pid, kill) || {_, Pid} <- Pids], % Убиваем все процессы
        exit(timeout)
    end;
wait_for_results(_, _, 0) -> ok.

%%% ТЕСТИРОВАНИЕ %%%
main(_) ->
    io:format("=== Testing star topology ===~n"),
    star(3, 2),
    timer:sleep(1000),
    
    io:format("~n=== Testing parent-children ===~n"),
    parent_children(2),
    send_to_child(1, hello),
    send_to_child(2, world),
    send_to_child(1, die),
    timer:sleep(500),
    send_to_child(1, "restarted"),
    timer:sleep(500),
    stop(),
    timer:sleep(500),
    
    io:format("~n=== Testing parallel foreach ===~n"),
    par_foreach(fun(X) -> 
                    timer:sleep(100),
                    io:format("Processing ~p in ~p~n", [X, self()]) 
                end, 
                [1,2,3,4,5], 
                [{processes, 3}, {sublist_size, 2}]),
    
    io:format("~nAll tests completed~n").