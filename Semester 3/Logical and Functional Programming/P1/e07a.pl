% 7. a. Write a predicate to compute the intersection of two sets.
checkListContainsElement([H|_], H):- !.
checkListContainsElement([H|T], E):-
    H =\= E,
    checkListContainsElement(T, E).

getIntersectionOfSets(_, [], []).
getIntersectionOfSets(S, [H|T], [H|R]):-
    checkListContainsElement(S, H), 
    getIntersectionOfSets(S, T, R), !.
getIntersectionOfSets(S, [H|T], R):-
    \+(checkListContainsElement(S, H)),
    getIntersectionOfSets(S, T, R), !.
