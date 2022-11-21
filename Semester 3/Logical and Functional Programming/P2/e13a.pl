% 13. a. Given a linear numerical list write a predicate to remove all sequences of consecutive values. Eg.: remove([1, 2, 4, 6, 7, 8, 10], L) will produce L=[4, 10].
removeSequencesOfConsecutiveValues([], []).
removeSequencesOfConsecutiveValues([E], [E]):- !.
removeSequencesOfConsecutiveValues([A, B], []):-
    A =:= B - 1, !.
removeSequencesOfConsecutiveValues([A, B], [A, B]):-
    A =\= B - 1, !.
removeSequencesOfConsecutiveValues([H1, H2, H3|T], R):-
    H1 =:= H2 - 1, 
    H2 =:= H3 - 1, !,
    removeSequencesOfConsecutiveValues([H2, H3|T], R).
removeSequencesOfConsecutiveValues([H1, H2, H3|T], R):-
    H1 =:= H2 - 1, 
    H2 =\= H3 - 1, !,
    removeSequencesOfConsecutiveValues([H3|T], R).
removeSequencesOfConsecutiveValues([H1, H2, H3|T], [H1|R]):-
    H1 =\= H2 - 1, !,
    removeSequencesOfConsecutiveValues([H2, H3|T], R).
