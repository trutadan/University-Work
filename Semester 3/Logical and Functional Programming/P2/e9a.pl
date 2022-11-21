% 9. a. For a list of integer number,write a predicate toadd in list after 1-st, 3-rd, 7-th, 15-th element a given value e.
addElementsInListAfterGivenPositions([], _, _, []).
addElementsInListAfterGivenPositions([H|T], CP, E, [H, E|R]):-
    (CP =:= 1; CP =:= 3; CP =:= 7; CP =:= 15), !,
    NewCP is CP + 1,
    addElementsInListAfterGivenPositions(T, NewCP, E, R).
addElementsInListAfterGivenPositions([H|T], CP, E, [H|R]):-
    NewCP is CP + 1, !, 
    addElementsInListAfterGivenPositions(T, NewCP, E, R).
    
mainAddElementsInListAfterGivenPositions(L, E, R):-
    addElementsInListAfterGivenPositions(L, 1, E, R).
