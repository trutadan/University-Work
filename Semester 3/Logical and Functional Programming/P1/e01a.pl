% 1. a. Write a predicate to determine the lowest common multiple of a list formed from integer numbers.
getGCD(0, N, N):- !.
getGCD(N, 0, N):- !.
getGCD(N1, N2, GCD):-
  N1 >= N2, !,
  NewN1 is N1 - N2,
  getGCD(NewN1, N2, GCD).
getGCD(N1, N2, GCD):-
  getGCD(N2, N1, GCD).

getLCM(N1, N2, LCM):-
	Product is N1 * N2,
  getGCD(N1, N2, GCD),
  LCM is Product / GCD.
    
getLCMOfList([], 1):- !.
getLCMOfList([H|T], ListLCM):-
  getLCMOfList(T, NewLCM), 
	getLCM(H, NewLCM, ListLCM).
