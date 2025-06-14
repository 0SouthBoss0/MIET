/*
1. Задайте функцию seconds(Hours, Minutes, Seconds), вычисляющую, сколько 
секунд прошло с начала дня по заданному времени (даны число часов, минут и секунд).
*/

seconds(Hours, Minutes, Seconds, TotalSeconds) :- TotalSeconds is Hours * 3600 + Minutes * 60 + Seconds.
% seconds(1, 2, 1, Ans) => 3721

/*
2. Задайте функцию min(List), возвращающую минимальный элемент списка List.
В случае пустого списка она должна выкидывать исключение.
*/

min([], _) :- throw(empty_list_exception).
min([X], X).
min([H|T], Min) :- min(T, MinTail), Min is min(H, MinTail).
% min([6,1,4], Min) => 1 

/*
3. Задайте функцию distinct(List), возвращающую true, если все элементы списка
List различаются (и false, если нет).
*/

distinct([]).
distinct([H|T]) :- not(member(H, T)), distinct(T). 

% distinct([4,2,a,false]) => true
% distinct([1,2,2,3]) => false

/*
4. Задайте функцию split_all(List, N), разбивающую список на части длиной N
каждая (возможно, кроме последней).
*/

split_all([], _, []).
split_all(List, N, [Sublist|Rest]) :-
    length(Sublist, N),
    append(Sublist, Tail, List),
    split_all(Tail, N, Rest).
split_all(List, _, [List]).
% split_all([1, 2, 3, 4, 5], 3, Ans) => [[1, 2, 3], [4, 5]] 

/*
5. Задайте функцию sublist(List, N, M), возвращающую отрезок списка List с N-ого
по M-ый элемент (нумерация начинается с первого).
*/

sublist(List, [N, M], Sublist) :-
    N > 0,
    M >= N,
    sublist_helper(List, N, M, 1, [], Sublist).

sublist_helper([], _, _, _, Acc, RevSublist) :-
    reverse(Acc, RevSublist).

sublist_helper([H|T], N, M, Pos, Acc, Sublist) :- (Pos >= N, Pos =< M -> 
                                                  sublist_helper(T, N, M, Pos + 1, [H|Acc], Sublist);   
                                                  sublist_helper(T, N, M, Pos + 1, Acc, Sublist)).

% sublist([1, 3, 4, 5, 6], [2, 4], Ans) => [3, 4, 5] 


/*
6. Задайте функцию intersect(List1, List2), находящую все общие элементы двух списков
List1 и List2.
*/

intersect([], _, []).
intersect([H|T], List2, Intersection) :- (member(H, List2) ->  intersect(T, List2, RestIntersection), 
                                         Intersection = [H|RestIntersection];   
                                         intersect(T, List2, Intersection)).

% intersect([1, 3, 2, 5], [2, 3, 4], Ans) => [3, 2]
% intersect([1, 6, 5], [2, 3, 4], Ans) => []. 


