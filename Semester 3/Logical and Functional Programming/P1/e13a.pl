% 13. a. Transform a list in a set, in the order of the last occurrences of elements. Eg.: [1,2,3,1,2] is transformed in [3,1,2].
countNumberOfOccurences([], _, 0).
countNumberOfOccurences([E|T], E, N):- !,
	  countNumberOfOccurences(T, E, NewN),
    N is NewN + 1.
countNumberOfOccurences([H|T], E, N):- 
    H =\= E, !,
    countNumberOfOccurences(T, E, N).

transformListInSetInLastOccurenceOrder([], []).
transformListInSetInLastOccurenceOrder([H|IT], [H|RT]):-
    countNumberOfOccurences(IT, H, N),
    N =:= 0, !,
    transformListInSetInLastOccurenceOrder(IT, RT).
transformListInSetInLastOccurenceOrder([IH|IT], RL):-
    countNumberOfOccurences(IT, IH, N),
    N =\= 0, !,
    transformListInSetInLastOccurenceOrder(IT, RL).
