% 11. a.
% substituteElement(l-list, OLD-old element, NEW-new element, R-result list)
% flow model(i, i, i, o)

substituteElement([], _, _, []).
substituteElement([H|T], OLD, NEW, [NEW|R]):-
    H =:= OLD,
    substituteElement(T, OLD, NEW, R).

substituteElement([H|T], OLD, NEW, [H|R]):-
    H =\= OLD,
    substituteElement(T, OLD, NEW, R).

% execution example: substituteElement([1, 2, 1, 3, 7, 1, 0, 11, 1], 1, 0, R).


% b.
% createSublist(l-list, M-sublist starting position, N-sublist end position, POS-current position, R-result list).
% flow model(i, i, i, 0, o)

createSublist([], _, _, _, []).
createSublist([H|T], M, N, POS, [H|R]):-
    POS > M - 1,
    POS < N + 1,
    createSublist(T, M, N, POS + 1, R).

createSublist([_|T], M, N, POS, R):-
    createSublist(T, M, N, POS + 1, R).

% execution example: createSublist([1, 2, 1, 3, 7, 1, 0, 11, 1], 1, 3, 0, R).