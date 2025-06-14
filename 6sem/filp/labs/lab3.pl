/*
1. Реализуйте функцию merge(bin_tree, bin_tree) -> bin_tree.merge(Tree1, Tree2).
Возвращает дерево, содержащее все элементы Tree1 и Tree2.
*/

% empty - пустое дерево
% tree(Value, Left, Right) - дерево с корнем Value и поддеревьями Left и Right
merge(empty, Tree, Tree).
merge(Tree, empty, Tree).
merge(tree(Element, Left1, Right1), Tree2, tree(Element, LeftMerged, RightMerged)) :-
    merge(Left1, Tree2, LeftMerged),
    merge(Right1, empty, RightMerged).

% merge(tree(1, tree(2, empty, tree(5, empty, empty)), empty), tree(3, tree(6, empty, empty), tree(7, empty, empty)), Result).

/*
2. Разработайте интерфейс для абстрактного типа данных "мультимножество" 
(см.https://ru.wikipedia.org/wiki/%D0%9C%D1%83%D0%BB%D1%8C%D1%82%D0%B8%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%BE). 
Мультимножество позволяет хранить произвольное число значений без
определённого порядка, при этом для каждого значение хранится также число раз,
которое этот объект входит в мультимножество).
*/

% Представление мультимножества: list(Pair), где Pair = (element, count)
% Пример:  [(a, 2), (b, 1), (c, 3)] представляет мультимножество, содержащее 'a' 2 раза, 'b' 1 раз и 'c' 3 раза.
empty_multiset([]).

% add(Element, Multiset1, Multiset2) - добавляет элемент в мультимножество.
add(Element, [], [(Element, 1)]).
add(Element, [(Element, Count)|Rest], [(Element, NewCount)|Rest]) :-
    NewCount is Count + 1.
add(Element, [(OtherElement, Count)|Rest1], [(OtherElement, Count)|Rest2]) :-
    Element \= OtherElement,
    add(Element, Rest1, Rest2).

% remove(Element, Multiset1, Multiset2) - удаляет элемент из мультимножества (уменьшает счетчик).
remove(Element, [(Element, 1)|Rest], Rest).
remove(Element, [(Element, Count)|Rest], [(Element, NewCount)|Rest]) :-
    Count > 1,
    NewCount is Count - 1.
remove(Element, [(OtherElement, Count)|Rest1], [(OtherElement, Count)|Rest2]) :-
    Element \= OtherElement,
    remove(Element, Rest1, Rest2).

% contains(Element, Multiset, Count) - проверяет, содержится ли элемент в мультимножестве, возвращает количество.
contains(Element, [(Element, Count)|_], Count).
contains(Element, [(OtherElement, _)|Rest], Count) :-
    Element \= OtherElement,
    contains(Element, Rest, Count).
contains(_, [], 0).

% add(a, [], Multiset1).
% add(b, [(a, 2)], Multiset2).
% remove(a, [(a, 2), (b, 1)], Multiset3).
% remove(a, [(a, 1), (b, 1)], Multiset4).
% contains(a, [(a, 2), (b, 1)], Count).

/*
3. Реализуйте над этим интерфейсом функцию union(multiset, multiset) -> bool.
union(Multiset1, Multiset2) возвращает мультимножество, содержащее все
элементы Multiset1 и Multiset2, причём кратности элементов складываются (т.е.
если X содержится 2 раза в MS1 и 3 раза в MS2, то оно содержится в union(MS1,
MS2) 5 раз).
*/

% union(Multiset1, Multiset2, Result) - объединяет два мультимножества, складывая кратности элементов.

% Базовый случай: если первое мультимножество пусто, результатом будет второе мультимножество.
union([], Multiset, Multiset).

% Рекурсивный случай: обрабатываем первый элемент первого мультимножества.
union([(Element, Count1)|Rest1], Multiset2, Result) :-
    % Пытаемся найти элемент (Element-Count2) во втором мультимножестве.
    (select((Element, Count2), Multiset2, Rest2) ->
        % Если элемент найден, складываем количества из обоих мультимножеств.
        NewCount is Count1 + Count2,
        % Рекурсивно вызываем union для оставшейся части первого мультимножества
        % и обновлённого второго мультимножества (с новым количеством для элемента).
        union(Rest1, [(Element, NewCount)|Rest2], Result);   
        % Если элемент не найден во втором мультимножестве,
        % просто добавляем его туда с текущим количеством.
        union(Rest1, [(Element, Count1)|Multiset2], Result)).

% union([(a-2), (b-1)], [(c-1)], Result).
% union([(a, 2), (b, 1)], [(a, 3), (c, 1)], Result).

/*
4. Разработайте 1 (для частичного зачёта) или 2 реализации этого интерфейса
*/

% Представление мультимножества: список элементов с повторениями
% Пример: [a, a, b, c, c, c] представляет мультимножество, содержащее 'a' 2 раза, 'b' 1 раз и 'c' 3 раза.

empty_multiset2([]).

add2(Element, Multiset, [Element|Multiset]).

remove2(Element, [Element|Rest], Rest).
remove2(Element, [OtherElement|Rest1], [OtherElement|Rest2]) :-
    Element \= OtherElement,
    remove2(Element, Rest1, Rest2).

contains2(Element, Multiset, Count) :-
    count_occurrences(Element, Multiset, Count).

count_occurrences(_, [], 0).
count_occurrences(Element, [Element|Rest], Count) :-
    count_occurrences(Element, Rest, RestCount),
    Count is RestCount + 1.
count_occurrences(Element, [OtherElement|Rest], Count) :-
    Element \= OtherElement,
    count_occurrences(Element, Rest, Count).

% union(Multiset1, Multiset2, Result) - объединяет два мультимножества, складывая кратности элементов.
union2([], Multiset, Multiset).
union2([Element|Rest], Multiset2, Result) :-
    % Добавляем элемент из первого мультимножества в результат
    add2(Element, Multiset2, TempMultiset),
    % Рекурсивно объединяем оставшуюся часть первого мультимножества с временным результатом
    union2(Rest, TempMultiset, Result).

% add2(a, [b, c], Multiset).
% add2(b, [a, b, c], Multiset).
% remove2(a, [a, a, b, c], Multiset).
% remove2(b, [a, a, b, c], Multiset).
% contains2(a, [a, a, b, c], Count).
% union2([a, a, b], [b, c, c], Result).
% union2([], [a, b, c], Result).

/*
5. Оцените алгоритмическую сложность реализаций, созданных в задании 4
*/

/*
Первая реализация (через список пар (Element, Count)):
add/3: В худшем случае O(n), где n — количество элементов в мультимножестве, так как нужно пройти по списку для поиска элемента.
remove/3: Аналогично add/3, O(n).
contains/3: O(n), так как нужно пройти по списку для поиска элемента.
union/3: O(n*m), где n и m — размеры двух мультимножеств, так как для каждого элемента первого мультимножества нужно пройти по второму.

Вторая реализация (через список с повторениями):
add2/3: O(1), так как добавление элемента в начало списка выполняется за константное время.
remove2/3: O(n), так как нужно пройти по списку для поиска и удаления элемента.
contains2/3: O(n), так как нужно пройти по списку для подсчёта вхождений.
union2/3: O(n), где n — количество элементов в первом мультимножестве
*/