/*
1. Реализуйте функцию list_heads(List), которая возвращает список первых
элементов непустых списков, входящих в List и игнорирует любые другие
элементы List.
*/

list_heads([], []).
list_heads([H|T], Result) :- (is_list(H), H = [Head|_] ->  Result = [Head|ResultTail], list_heads(T, ResultTail);
                             list_heads(T, Result)).
% list_heads([[1,2,3], {true,3}, [4,5], []], Ans) => [1,4]


/*
2. Не смотря на определение в модуле lists стандартной библиотеки, реализуйте
функцию takewhile(Pred, List). Она возвращает такой начальный отрезок списка
List, для всех элементов которого Pred возвращает true. В отличие от filter, она
заканчивает работу, как только найдёт элемент, на котором Pred вернёт false.
*/

takewhile(_, [], []).
takewhile(Pred, [Head|Tail], Result) :- (call(Pred, Head) ->
        Result = [Head|ResultTail], takewhile(Pred, Tail, ResultTail);
        Result = []).
% takewhile(number, [1, 2, a, 4], Result) => [1, 2]

/*
3. Реализуйте функцию iterate(F, N), которая возвращает функцию, применяющую
F к своему аргументу N раз (т.е., например, (iterate(F, 2))(X) == F(F(X)))
*/

iterate(_, 0, X, X).
iterate(F, N, X, Result) :- N > 0, call(F, X, X1), N1 is N - 1, iterate(F, N1, X1, Result).
% iterate(plus(2), 3, 0, Result) => 6


/* 4. Реализуйте функцию integrate(F, N), принимающую функцию F из
действительных чисел в действительные числа) и целое число N, и возвращающую
функцию 2 аргументов: (integrate(F, N))(A, B) приближенно равно определённому
интегралу F от A до B (для подсчёта которого отрезок разбивается на N частей).
*/

integrate(F, N, A, B, Result) :-
    Delta is (B - A) / N,
    integrate_loop(F, N, A, Delta, 0, Result).
integrate_loop(_, 0, _, _, Acc, Acc).
integrate_loop(F, N, X, Delta, Acc, Result) :- N > 0, call(F, X, Y), 
    NewAcc is Acc + Y * Delta, NewX is X + Delta, N1 is N - 1,
    integrate_loop(F, N1, NewX, Delta, NewAcc, Result).

% integrate(sin, 1000, 0, pi, Result) => 2
linear(X, Y) :- Y is X.
% integrate(linear, 100000, 0, 1, Result) => 50

/*
5. Реализуйте функцию for(Init, Cond, Step, Body), которая работает как цикл for (I = Init;
Cond(I); I = Step(I)) { Body(I) } в C-подобных языках:
поддерживается "текущее значение" I. В начале это Init.
на каждом шаге проверяется, выполняется ли условие Cond(I).
если да, то вызывается функция Body(I). Потом вычисляется новое значение как Step(I)
и возвращаемся к проверке Cond.
если нет, то работа функции заканчивается. 
*/
for(I, Cond, Step, Body) :- (call(Cond, I) -> call(Body, I), call(Step, I, NextI), 
                            for(NextI, Cond, Step, Body); true).
cond(I) :- I =< 5.
step(I, NextI) :-NextI is I + 1.
body(I) :- write(I), nl.
% for(1, cond, step, body) => 1, 2, 3, 4, 5

/*
6. Реализуйте функцию sortBy(Comparator, List), которая сортирует список List, используя
Comparator для сравнения элементов. Comparator(X, Y) возвращает один из атомов less
(если X < Y), equal (X == Y), greater (X > Y) для любых элементов List. Можете
использовать любой алгоритм сортировки, но укажите, какой именно. Сортировка
слиянием очень хорошо подходит для связных списков. 
*/

sortBy(_, [], []).
sortBy(_, [X], [X]).
sortBy(Comparator, List, Sorted) :- split(List, Left, Right), sortBy(Comparator, Left, SortedLeft),
    sortBy(Comparator, Right, SortedRight), merge(Comparator, SortedLeft, SortedRight, Sorted).

split(List, Left, Right) :- length(List, Len), Half is Len // 2, split(List, Half, Left, Right).
split(List, 0, [], List).
split([X|Xs], N, [X|Left], Right) :- N > 0, N1 is N - 1, split(Xs, N1, Left, Right).

merge(_, [], Right, Right).
merge(_, Left, [], Left).
merge(Comparator, [X|Xs], [Y|Ys], [X|Zs]) :- call(Comparator, X, Y, less), merge(Comparator, Xs, [Y|Ys], Zs).
merge(Comparator, [X|Xs], [Y|Ys], [Y|Zs]) :- call(Comparator, X, Y, greater), merge(Comparator, [X|Xs], Ys, Zs).
merge(Comparator, [X|Xs], [Y|Ys], [X|Zs]) :- call(Comparator, X, Y, equal), merge(Comparator, Xs, Ys, Zs).

compare_numbers(X, Y, less) :- X < Y.
compare_numbers(X, Y, equal) :- X =:= Y.
compare_numbers(X, Y, greater) :- X > Y.

% sortBy(compare_numbers, [3, 1, 4, 1, 5, 9, 2, 6, 5], Sorted) => [1, 2, 3, 4, 5, 6, 9]
