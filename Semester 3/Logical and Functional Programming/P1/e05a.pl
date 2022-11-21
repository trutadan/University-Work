% 5. a. Write a predicate to compute the union of two sets.
checkListContainsElement([H|_], H):- !.
checkListContainsElement([H|T], E):-
    H =\= E,
    checkListContainsElement(T, E).

getUnionOfSets([], [], []).
getUnionOfSets(S, [], S).
getUnionOfSets(S, [H|T], R):-
    checkListContainsElement(S, H),
    getUnionOfSets(S, T, R), !.
getUnionOfSets(S, [H|T], [H|R]):-
    \+(checkListContainsElement(S, H)),
    getUnionOfSets(T, S, R), !.
