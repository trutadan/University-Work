% 3. a. Define a predicate to remove from a list all repetitive elements. Eg.: l=[1,2,1,4,1,3,4] => l=[2,3])
countNumberOfValueFromList([], _, 0).
countNumberOfValueFromList([H|T], H, C):-
    countNumberOfValueFromList(T, H, NewC),
    C is NewC + 1.
countNumberOfValueFromList([H|T], V, C):-
    H =\= V,
    countNumberOfValueFromList(T, V, C), !.

removeElementFromList([], _, []).
removeElementFromList([E|T], E, RT):-
    removeElementFromList(T, E, RT), !.
removeElementFromList([H|T], E, [H|RT]):-
    H =\= E, 
	removeElementFromList(T, E, RT).	

removeRepetitiveElementsFromList([], []).
removeRepetitiveElementsFromList([H|T], [H|R]):-
    countNumberOfValueFromList(T, H, C),
    C =:= 0, !,
    removeRepetitiveElementsFromList(T, R).
removeRepetitiveElementsFromList([H|T], R):-
    countNumberOfValueFromList(T, H, C),
    C =\= 0, !,
    removeElementFromList([H|T], H, RL),
    removeRepetitiveElementsFromList(RL, R).
