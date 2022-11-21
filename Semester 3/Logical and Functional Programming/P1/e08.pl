% 8. a. Write a predicate to determine if a list has even numbers of elements 
% without counting the elements from the list.
checkIfListHasEvenNumberOfElements([]).
checkIfListHasEvenNumberOfElements([_, _|T]) :- 
    checkIfListHasEvenNumberOfElements(T).

% b. Write a predicate to delete first occurrence of the minimum number from a list.
findMinimumNumberFromAList([E], E):- !.
findMinimumNumberFromAList([H|T], H):-
    findMinimumNumberFromAList(T, E), 
    H < E, !.
findMinimumNumberFromAList([_|T], E):-
    findMinimumNumberFromAList(T, E).

deleteFirstOccurenceOfNumberInList([H|T], H, T).
deleteFirstOccurenceOfNumberInList([H|T], E, [H|R]):-
    deleteFirstOccurenceOfNumberInList(T, E, R).

deleteFirstOccurenceOfMinimumNumberFromList(L, R):-
    findMinimumNumberFromAList(L, M),
    deleteFirstOccurenceOfNumberInList(L, M, R), !.
