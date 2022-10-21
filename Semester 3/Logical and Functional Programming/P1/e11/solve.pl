% 11. a.
% substituteElement(L-list, OLD-old element, NEW-new element, R-result list)
% flow model(i, i, i, o), (i, i, i, i)

substituteElement([], _, _, []).
substituteElement([H|T], OLD, NEW, [NEW|R]):-
    H =:= OLD,
    !,
    substituteElement(T, OLD, NEW, R).

substituteElement([H|T], OLD, NEW, [H|R]):-
    H =\= OLD,
    substituteElement(T, OLD, NEW, R).

% execution example: substituteElement([1, 2, 1, 3, 7, 1, 0, 11, 1], 1, 0, R).


% b.
% createSublist(L-list, M-sublist starting position, N-sublist end position, POS-current position, R-result list).
% flow model(i, i, i, i, o), (i, i, i, i, i)

createSublist([], _, _, _, []).
createSublist([H|T], M, N, POS, [H|R]):-
    POS > M - 1,
    POS < N + 1,
    !,
    NEWPOS is POS + 1,
    createSublist(T, M, N, NEWPOS, R).

createSublist([_|T], M, N, POS, R):-
    NEWPOS is POS + 1,
    createSublist(T, M, N, NEWPOS, R).

% mainCreateSublist(L-list, M-sublist starting position, N-sublist end position, R-result list).
% flow model(i, i, i, o), (i, i, i, i)

mainCreateSublist(L, M, N, R):-
    createSublist(L, M, N, 0, R).

% execution example: mainCreateSublist([1, 2, 1, 3, 7, 1, 0, 11, 1], 1, 3, R).