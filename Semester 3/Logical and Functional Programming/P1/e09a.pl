% 9. a. Insert an element on the position n in a list.
insertElementOnGivenPosition([], _, _, _, []).
insertElementOnGivenPosition([H|T], E, GP, GP, [E|R]):-
    NewCP is GP + 1,
    insertElementOnGivenPosition([H|T], E, GP, NewCP, R), !.
insertElementOnGivenPosition([H|T], E, GP, CP, [H|R]):-
    GP =\= CP, !,
    NewCP is CP + 1,
    insertElementOnGivenPosition(T, E, GP, NewCP, R).
	
mainInsertElementOnGivenPosition(L, E, GP, R):-
    insertElementOnGivenPosition(L, E, GP, 1, R).
