/*
1. Постройте деревья вызова для запросов:
*/

% Факты о родственных связях
родитель(алексей, борис).
родитель(борис, сергей).

% Предикат для определения отношения предок-потомок
предок_потомок(X, Y) :- 
    format('Первое правило вызвано с X = ~w, Y = ~w~n', [X, Y]),
    родитель(X, Y),
    format('Первое правило истинно с X = ~w, Y = ~w~n', [X, Y]).

предок_потомок(X, Y) :- 
    format('Второе правило вызвано с X = ~w, Y = ~w~n', [X, Y]),
    родитель(X, Z),
    format('Рекурсивный вызов для Z = ~w, Y = ~w~n', [Z, Y]),
    предок_потомок(Z, Y),
    format('Второе правило истинно с X = ~w, Y = ~w~n', [X, Y]).

test_предок(прямой_родственник) :- предок_потомок(алексей, борис).
test_предок(непрямой_родственник) :- предок_потомок(алексей, сергей).
test_предок(не_родственник) :- \+ предок_потомок(сергей, алексей).

% Предикат my_member проверяет принадлежность элемента списку
my_member(X, [X|_]) :-
    format('Первое правило my_member: X = ~w, голова списка = ~w~n', [X, X]),
    format('Успех: X найден в голове списка~n').

my_member(X, [_|Tail]) :-
    format('Второе правило my_member: пропускаем голову, ищем X = ~w в хвосте ~w~n', [X, Tail]),
    my_member(X, Tail),
    format('Успех: X = ~w найден в хвосте списка~n', [X]).

test_member(member_head) :- my_member(1, [1,2,3]).
test_member(member_tail) :- my_member(2, [1,2,3]).
test_member(member_last) :- my_member(3, [1,2,3]).
test_member(fail_for_non_member) :- \+ my_member(4, [1,2,3]).

/*
2. Предикат ordered(List) проверяет, что элементы списка - числа в порядке возрастания
*/

ordered([]).
ordered([_]).

ordered([X, Y | T]) :- 
    number(X),
    number(Y),
    X =< Y,
    ordered([Y | T]).

test_ordered(empty_list) :- ordered([]).
test_ordered(single_element) :- ordered([5]).
test_ordered(ordered_list) :- ordered([1, 2, 3, 4]).
test_ordered(unordered_list) :- \+ ordered([3, 2, 1]).
test_ordered(mixed_types) :- \+ ordered([1, a]).

/*
3. Предикат sublist(List1, List2) проверяет, что List2 - подсписок List1
*/

sublist(_, []).                                
sublist([X | T], [X | T2]) :- prefix(T, T2).   
sublist([_ | T], L) :- sublist(T, L).          

% Проверяем, что один список является префиксом другого
prefix(_, []).
prefix([X | T], [X | T2]) :- prefix(T, T2).

% Тесты для предиката sublist
test_sublist(empty_sublist) :- sublist([a, b, c], []).
test_sublist(full_sublist) :- sublist([a, b, c], [a, b, c]).
test_sublist(prefix_sublist) :- sublist([a, b, c], [a, b]).
test_sublist(suffix_sublist) :- sublist([a, b, c], [b, c]).
test_sublist(middle_sublist) :- sublist([a, b, c, d], [b, c]).
test_sublist(non_sublist) :- \+ sublist([a, b, c], [a, c]).

/*
4. Предикат my_flatten(NestedList, FlattenedList) "расплющивает" вложенные списки
*/

my_flatten([], []).

my_flatten([H|T], Flattened) :-
    my_flatten(H, FlattenedH),
    my_flatten(T, FlattenedT),
    append(FlattenedH, FlattenedT, Flattened).

my_flatten(Atom, [Atom]) :- atomic(Atom).

test_flatten(empty_list) :- my_flatten([], []).
test_flatten(flat_list) :- my_flatten([1, 2, 3], [1, 2, 3]).
test_flatten(nested_list) :- my_flatten([a, [b, [c]], d], [a, b, c, d]).
test_flatten(deeply_nested) :- my_flatten([[[[a]]]], [a]).
test_flatten(mixed_elements) :- my_flatten([1, [2, [three], 4]], [1, 2, three, 4]).

/*
5. Генерация кода Грея для n бит
Код Грея - последовательность двоичных чисел, где соседние числа отличаются на 1 бит
*/

gray([_], [[0], [1]]).

gray([_|Rest], Code) :-
    % Шаг 1: генерируем код для N-1 бит
    gray(Rest, PreviousCode),

    % Шаг 2: переворачиваем полученный код
    reverse(PreviousCode, ReversedCode),

    % Шаг 3: добавляем 0 к каждому коду из исходного списка
    add_bit(0, PreviousCode, ZeroPrefixedCode),

    % Шаг 4: добавляем 1 к каждому коду из перевернутого списка
    add_bit(1, ReversedCode, OnePrefixedCode),

    % Шаг 5: объединяем оба списка
    append(ZeroPrefixedCode, OnePrefixedCode, Code).

add_bit(_, [], []).
add_bit(Bit, [Code|Rest], [[Bit|Code]|PrefixedRest]) :- 
    add_bit(Bit, Rest, PrefixedRest).

test_gray(gray_code_1bit) :- gray([a], [[0], [1]]).
test_gray(gray_code_2bits) :- gray([a, b], [[0,0], [0,1], [1,1], [1,0]]).
test_gray(gray_code_3bits) :- gray([a, b, c], [[0,0,0], [0,0,1], [0,1,1], [0,1,0], 
                                              [1,1,0], [1,1,1], [1,0,1], [1,0,0]]).