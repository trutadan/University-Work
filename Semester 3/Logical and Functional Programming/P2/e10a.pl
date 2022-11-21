% 10. a. For a list of integer numbers, define a predicate to write twice in list every prime number.
isXdivisibleByY(X, Y):- 
    0 is X mod Y, !.
isXdivisibleByY(X, Y):- 
    X > Y + 1,
    NewY is Y + 1,
    isXdivisibleByY(X, NewY).

isPrime(2):- 
    true, !.
isPrime(X):- 
    X < 2, !,
    false.
isPrime(X):- 
    not(isXdivisibleByY(X, 2)).

doublePrimeNumbersInList([], []).
doublePrimeNumbersInList([H|T], [H, H|R]):-
    isPrime(H), !,
    doublePrimeNumbersInList(T, R).
doublePrimeNumbersInList([H|T], [H|R]):-
    not(isPrime(H)), !,
    doublePrimeNumbersInList(T, R).
