% 8. a. Determine the successorof a number represented as digits in a list. Eg.: [1 9 3 5 9 9] --> [1 9 3 6 0 0].
getSuccesorOfNumber([], _, []).
getSuccesorOfNumber([0], 1, [1]).
getSuccesorOfNumber([N], 0, [NR]):-
    NR is N + 1.
getSuccesorOfNumber([9|T], 1, [0|R]):-
    getSuccesorOfNumber(T, 1, R).
getSuccesorOfNumber([H|T], 0, [TA|R]):-
	  getSuccesorOfNumber(T, A, R),
	  TA is A + H, !.

mainGetSuccesorOfNumber(L, R):-
    getSuccesorOfNumber(L, 0, R).
