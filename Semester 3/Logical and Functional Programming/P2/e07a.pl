% 7. a. Determine the position of the maximal element of a linear list. Eg.: maxpos([10,14,12,13,14], L) produces L = [2,5].
getMaximumValueOfList([X], X):- !.
getMaximumValueOfList([H|T], H):-
    getMaximumValueOfList(T, R),
    H > R, !.
getMaximumValueOfList([H|T], R):-
    getMaximumValueOfList(T, R),
    H =< R.

getPositionsOfGivenElement([], _, _, []).
getPositionsOfGivenElement([E|T], E, CP, [CP|R]):- !,
    NewCP is CP + 1,
	  getPositionsOfGivenElement(T, E, NewCP, R).
getPositionsOfGivenElement([H|T], E, CP, R):-
    H =\= E, !,
    NewCP is CP + 1,
	  getPositionsOfGivenElement(T, E, NewCP, R).
getPositionOfMaximalElement(L, R):-
    getMaximumValueOfList(L, M),
    getPositionsOfGivenElement(L, M, 1, R).
