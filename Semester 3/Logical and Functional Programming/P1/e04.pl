% 4. a. Write a predicate to determine the difference of two sets.
checkIfElementInList([H|T], E):-
    E =\= H, !,
    checkIfElementInList(T, E).
checkIfElementInList([H|_], H).

getDifferenceOfTwoSets([], _, []).
getDifferenceOfTwoSets([H|T], L, R) :-
    checkIfElementInList(L, H),
    getDifferenceOfTwoSets(T, L, R), !.
getDifferenceOfTwoSets([H|T], L, [H|R]) :-
    getDifferenceOfTwoSets(T, L, R).

% b. Write a predicate to add value 1 after every even element from a list.
add1AfterEvenElementsInList([], []).
add1AfterEvenElementsInList([H|T], [H, 1|R]):-
    H mod 2 =:= 0, !,
    add1AfterEvenElementsInList(T, R).
add1AfterEvenElementsInList([H|T], [H|R]):-
    H mod 2 =:= 1, !,
    add1AfterEvenElementsInList(T, R).
