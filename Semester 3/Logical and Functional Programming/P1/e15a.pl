% 15. a. Write a predicate to transform a list in a set, considering the first occurrence. Eg: [1,2,3,1,2] is transform in [1,2,3].
removeElementFromList([], _, []).
removeElementFromList([E|T], E, RT):-
    removeElementFromList(T, E, RT), !.
removeElementFromList([H|T], E, [H|RT]):-
    H =\= E, 
	  removeElementFromList(T, E, RT).

transformListInSetInFirstOccurenceOrder([], []).
transformListInSetInFirstOccurenceOrder([H|T], [H|R]):-
    removeElementFromList(T, H, RL),
    transformListInSetInFirstOccurenceOrder(RL, R).
