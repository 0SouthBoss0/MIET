/*
1. Предикат neq(X, Y) реализует отрицание равенства без использования оператора \+
   Эквивалентно \+ (X == Y), но реализовано через комбинацию отсечения и fail
*/

neq(X, Y) :- X == Y, !, fail.
neq(_, _).

test_neq(same_vars) :- \+ neq(X, X).      
test_neq(diff_vars) :- neq(_, _).          
test_neq(same_values) :- \+ neq(4, 4). 
test_neq(diff_values) :- neq(4, 5).  

/*
2. Предикат split(List, Pos, NonPos) разделяет список чисел на положительные и неположительные
   Pos - подсписок положительных чисел в исходном порядке
   NonPos - подсписок нулей и отрицательных чисел в исходном порядке
*/

% Версия без сечений

split([], [], []).
split([H|T], [H|Pos], NonPos) :- H > 0, split(T, Pos, NonPos).
split([H|T], Pos, [H|NonPos]) :- H =< 0, split(T, Pos, NonPos).

% Версия с зелёными сечениями

split_opt([], [], []) :- !.
split_opt([H|T], [H|Pos], NonPos) :- H > 0, !, split_opt(T, Pos, NonPos).
split_opt([H|T], Pos, [H|NonPos]) :- split_opt(T, Pos, NonPos).

test_split(empty) :- split([], [], []).             
test_split(positive) :- split([1,2,3], [1,2,3], []).  
test_split(nonpos) :- split([0,-1,-2], [], [0,-1,-2]). 
test_split(mixed) :- split([1,-2,3,0], [1,3], [-2,0]). 

test_split_opt(empty) :- split_opt([], [], []).               
test_split_opt(positive) :- split_opt([1,2,3], [1,2,3], []).
test_split_opt(nonpos) :- split_opt([0,-1,-2], [], [0,-1,-2]).
test_split_opt(mixed) :- split_opt([1,-2,3,0], [1,3], [-2,0]).

/*
3. Предикат delete_all(List, X, Result) удаляет все вхождения элемента X из списка List
   Результат сохраняет порядок оставшихся элементов
*/

delete_all([], _, []).
delete_all([X|T], X, Result) :- delete_all(T, X, Result).
delete_all([H|T], X, [H|Result]) :- H \= X, delete_all(T, X, Result). 

test_delete_all(empty_list) :- delete_all([], 1, []).               
test_delete_all(no_occurrences) :- delete_all([1, 2, 3], 4, [1, 2, 3]). 
test_delete_all(all_occurrences) :- delete_all([1, 1, 1], 1, []).   
test_delete_all(some_occurrences) :- delete_all([1, 2, 3, 2, 4], 2, [1, 3, 4]). 
test_delete_all(mixed_types) :- delete_all([a, b, a, c], a, [b, c]). 