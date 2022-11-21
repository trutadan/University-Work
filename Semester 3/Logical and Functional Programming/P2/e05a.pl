% 5. a. Substitute all occurrencesof an element of a list with all the elementsof another list. Eg. subst([1,2,1,3,1,4],1,[10,11],X) produces X=[10,11,2,10,11,3,10,11,4].
appendListElementsToAnotherList([], L, L).
appendListElementsToAnotherList([H|T], L, [H|R]):-
    appendListElementsToAnotherList(T, L, R).

substituteElementWithAllElementsOfList([], _, _, []).
substituteElementWithAllElementsOfList([H|T], E, EL, R):-
    H =:= E, !,
    appendListElementsToAnotherList(EL, T, RL),
    substituteElementWithAllElementsOfList(RL, E, EL, R).
substituteElementWithAllElementsOfList([H|T], E, EL, [H|R]):-
    H =\= E, !,
    substituteElementWithAllElementsOfList(T, E, EL, R).
