% 11. a. Replace all occurrences of an element from a list with another element e.
replaceElementFromListWithAnotherElement([], _, _, []).
replaceElementFromListWithAnotherElement([H|T], H, NE, [NE|R]):- !,
	replaceElementFromListWithAnotherElement(T, H, NE, R).
replaceElementFromListWithAnotherElement([H|T], E, NE, [H|R]):-
        H =\= E, !,
	replaceElementFromListWithAnotherElement(T, E, NE, R).
