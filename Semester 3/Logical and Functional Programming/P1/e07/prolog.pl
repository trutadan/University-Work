% 7. a.
% searchElementInSet(E-searched element, L-list)
% flow model(i, i)

searchElementInSet(E, [E|_]):-!.

searchElementInSet(E, [_|T]):-
    searchElementInSet(E, T).

% intersectSets(S1-first set, S2-second set, RS-resulting set)
% flow model(i, i, o)

intersectSets([], _, []).
intersectSets([H|T], S2, RS):-
    searchElementInSet(H, S2),
    intersectSets(T, S2, R),
    RS = [H|R],
    !.

intersectSets([_|T], S2, RS):-
    intersectSets(T, S2, RS).

% execution example: intersectSets([2, 1, 5, 4, -1, 3], [1, -2, 3, 5], R).


% b.
% createList(M-starting interval number, N-ending interval number, L-list)
% flow model(i, i, o), (i, i, i)

createList(M, N, []):-
    M > N,
    !.

createList(M, N, [M|R]):-
    NewM is M + 1,
    createList(NewM, N, R).

% execution example: searchElementInSet(2, [1, -2, 3, 5]).