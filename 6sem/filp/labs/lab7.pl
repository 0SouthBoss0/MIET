/* 
1. Предикат fib(N, NthFib) вычисляет N-ное число Фибоначчи (нумерация с 1)
   Последовательность Фибоначчи: 1, 1, 2, 3, 5, 8, 13, ...
*/

fib(1, 1).
fib(2, 1).

fib(N, NthFib) :- 
    N > 2,
    N1 is N - 1,
    N2 is N - 2,
    fib(N1, F1),
    fib(N2, F2),
    NthFib is F1 + F2.

test_fib(fib_1) :- fib(1, 1).
test_fib(fib_2) :- fib(2, 1).
test_fib(fib_3) :- fib(3, 2).
test_fib(fib_5) :- fib(5, 5).
test_fib(not_fib_5) :- \+ fib(5, 6).

/* 
2. Предикат mean(List, Mean) вычисляет среднее арифметическое списка чисел
*/

mean(List, Mean) :-
    sum_list(List, Sum),
    length(List, Length),
    Length > 0, 
    Mean is Sum / Length.

test_mean(mean_single) :- mean([5], 5).
test_mean(mean_three) :- mean([1,2,3], 2).
test_mean(mean_float) :- mean([1,2,3,4], 2.5).
test_mean(not_mean_float) :- \+ mean([1,2,3,4], 2.6).

/* 
3. Предикат dnf(Formula) проверяет, является ли формула дизъюнктивной нормальной формой (ДНФ)
ДНФ - это дизъюнкция конъюнктов литералов
*/

% Определение операторов для удобного представления формул
:- op(800, fx, \+).
:- op(900, xfy, /\).
:- op(910, xfy, \/).

dnf(Formula) :- is_dnf(Formula).

% ДНФ - это дизъюнкция конъюнктов
is_dnf(Formula \/ Rest) :- is_conjunct(Formula), is_dnf(Rest).
is_dnf(Formula) :- is_conjunct(Formula).

% Конъюнкт - это конъюнкция литералов
is_conjunct(Formula /\ Rest) :- is_literal(Formula), is_conjunct(Rest).
is_conjunct(Formula) :- is_literal(Formula).


is_literal(Atom) :- atom(Atom).
is_literal(\+ Atom) :- atom(Atom).

test_dnf(simple_atom) :- dnf(a).
test_dnf(simple_negation) :- dnf(\+a).
test_dnf(single_conjunct) :- dnf(a /\ b).
test_dnf(simple_disjunction) :- dnf(a \/ b). 
test_dnf(complex_dnf) :- dnf((x /\ (\+ y) /\ z) \/ ((\+ x) /\ z)). 
test_dnf(not_dnf) :- \+ dnf((x \/ (\+ y)) /\ (z \/ (\+ x) \/ y)).
test_dnf(not_dnf1) :- \+ dnf(a /\ (b \/ c)). 
test_dnf(not_dnf2) :- \+ dnf((a \/ b) /\ (c \/ d)).

/* 
4. Предикат eval_logic(Formula, Values) вычисляет значение логической формулы
   Values - список значений переменных в формате true(Var) или false(Var)
*/

% Дополнительные операторы для логических формул
:- op(920, xfy, ->). 
:- op(930, xfy, <->).

eval_logic(Atom, Values) :-
    atom(Atom),
    (memberchk(true(Atom), Values) -> true); 
     (memberchk(false(Atom), Values) -> fail ; fail).


eval_logic(\+ Formula, Values) :- \+ eval_logic(Formula, Values).
eval_logic(Formula1 /\ Formula2, Values) :- eval_logic(Formula1, Values), eval_logic(Formula2, Values).
eval_logic(Formula1 \/ Formula2, Values) :- (eval_logic(Formula1, Values) ; eval_logic(Formula2, Values)).
eval_logic(Formula1 -> Formula2, Values) :- (eval_logic(Formula1, Values) -> eval_logic(Formula2, Values) ; true).
eval_logic(Formula1 <-> Formula2, Values) :- eval_logic(Formula1 -> Formula2, Values), 
    eval_logic(Formula2 -> Formula1, Values).

test_eval(true_atom) :- eval_logic(a, [true(a)]).
test_eval(false_atom) :- \+ eval_logic(a, [false(a)]).
test_eval(missing_atom) :- \+ eval_logic(a, [true(b)]). 
test_eval(simple_conj_true) :- eval_logic(a /\ b, [true(a), true(b)]). 
test_eval(simple_conj_false) :- \+ eval_logic(a /\ b, [true(a), false(b)]).
test_eval(simple_disj_true) :- eval_logic(a \/ b, [true(a), false(b)]).
test_eval(simple_disj_false) :- \+ eval_logic(a \/ b, [false(a), false(b)]).
test_eval(negation_true) :- eval_logic(\+a, [false(a)]). 
test_eval(negation_false) :- \+ eval_logic(\+a, [true(a)]).
test_eval(implication_true1) :- eval_logic(a -> b, [false(a), true(b)]). 
test_eval(implication_true2) :- eval_logic(a -> b, [true(a), true(b)]). 
test_eval(implication_false) :- \+ eval_logic(a -> b, [true(a), false(b)]).
test_eval(equiv_true) :- eval_logic(a <-> b, [true(a), true(b)]).
test_eval(equiv_false) :- \+ eval_logic(a <-> b, [true(a), false(b)]).
test_eval(complex_formula1) :- eval_logic((a \/ b) /\ (c -> d), [false(a), true(b), false(c), true(d)]). 
test_eval(complex_formula2) :- \+ eval_logic((a /\ b) \/ (c <-> d), [false(a), true(b), true(c), false(d)]). 

/* 
5. Предикат prime_factors(Num, Factors) находит простые делители числа и их кратность
   Результат возвращается в виде списка factor(Prime, Power)
*/


prime_factors(Num, Factors) :-
    integer(Num),      
    Num > 1,          
    prime_factors(Num, 2, [], RevFactors),
    reverse(RevFactors, Factors). 

% Базовый случай: число стало 1 - завершаем обработку
prime_factors(1, _, Factors, Factors) :- !.
prime_factors(Num, Div, Acc, Factors) :-
    Div =< Num,             
    (Num mod Div =:= 0 ->   % Если Div делит Num
        count_divisors(Num, Div, 0, Count, NewNum), % Считаем степень делителя
        NextDiv is Div + 1,
        prime_factors(NewNum, NextDiv, [factor(Div, Count)|Acc], Factors) % Добавляем делитель в аккумулятор
    ;
        NextDiv is Div + 1,
        prime_factors(Num, NextDiv, Acc, Factors)
    ).

% Подсчет количества делителей Div в числе Num
count_divisors(Num, Div, Acc, Count, NewNum) :-
    Num mod Div =:= 0, !,                     
    NextNum is Num div Div,
    NewAcc is Acc + 1,    
    count_divisors(NextNum, Div, NewAcc, Count, NewNum). 
count_divisors(Num, _, Acc, Acc, Num).

test_prime(simple_case) :- prime_factors(12, [factor(2, 2), factor(3, 1)]).
test_prime(prime_number) :- prime_factors(7, [factor(7, 1)]).
test_prime(complex_case) :- prime_factors(315, [factor(3, 2), factor(5, 1), factor(7, 1)]). 
test_prime(power_of_prime) :- prime_factors(8, [factor(2, 3)]). 
test_prime(large_number) :- prime_factors(360, [factor(2, 3), factor(3, 2), factor(5, 1)]). 
test_prime(not_integer) :- \+ prime_factors(12.5, _). 
test_prime(less_than_2) :- \+ prime_factors(1, _). 