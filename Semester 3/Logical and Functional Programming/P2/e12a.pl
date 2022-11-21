% 12. a. Define a predicate to add after every element from a list, the divisors of that number.
insertAfterElementTheDivisorsOfThatNumber(N, _, L, L):- 
    N =< 2, !.
insertAfterElementTheDivisorsOfThatNumber(N, N, L, L):- !.
insertAfterElementTheDivisorsOfThatNumber(N, D, L, [D|R]):- 
    N mod D =:= 0, !,
    NewD is D + 1,
    insertAfterElementTheDivisorsOfThatNumber(N, NewD, L, R).
insertAfterElementTheDivisorsOfThatNumber(N, D, L, R) :-
    NewD is D + 1,
    insertAfterElementTheDivisorsOfThatNumber(N, NewD, L, R).

mainInsertAfterElementTheDivisorsOfThatNumber([], []).
mainInsertAfterElementTheDivisorsOfThatNumber([H|T], [H|R]) :-
    mainInsertAfterElementTheDivisorsOfThatNumber(T, RD),
    insertAfterElementTheDivisorsOfThatNumber(H, 2, RD, R).
