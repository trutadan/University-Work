; 1.
; a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.

; math model
; getNthElementOfList(l1l2...ln, pos, N) = nil if n = 0,
;                                        = l1 if pos = N,
;                                        = getNthElementOfList(l2...ln, pos + 1, N) otherwise;

(DEFUN getNthElementOfList (l pos N)
       (COND
        ((null l) nil)
        ((equal pos N) (car l))
        (t (getNthElementOfList (cdr l) (+ 1 pos) N))
       )
)

(DEFUN mainGetNthElementOfList (l N)
    (getNthElementOfList l 1 N)
)

(print (mainGetNthElementOfList '(1 2 3) 5))


; b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.

; math model
; checkMemberOfList(l1l2...ln, E) = false if n = 0, 
;                                 = checkMemberOfList(l1, E) + checkMemberOfList(l2...ln, E) if l1 is a list,
;                                 = true if l1 = E,
;                                 = checkMemberOfList(l2...ln, E) if l1 != E, otherwise;

(DEFUN checkMemberOfList (l E)
        (COND
           ((null l) nil)
           ((listp (car l)) (or (checkMemberOfList (car l) E) (checkMemberOfList (cdr l) E)))
           ((equal (car l) E) t)
           (t (checkMemberOfList (cdr l) E))
     )
)

(print (checkMemberOfList '(1 2 3) 3))

; c) Write a function to determine the list of all sublists of a given list, on any level.
; A sublist is either the list itself, or any element that is a list, at any level. Example:
; (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists:
; ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )

; math model
; mapGetAllSublistsOfGivenList(l) = () if l is null,
;                                 = () if l is atom,
;                                 = (l1l2...ln) + (mapGetAllSublistsOfGivenList(l1)) + (mapGetAllSublistsOfGivenList(l2)) + ... + (mapGetAllSublistsOfGivenList(ln)), where l = l1l2...ln, otherwise;

(DEFUN mapGetAllSublistsOfGivenList (l)
           (COND
            ((null l) nil)
            ((atom l) nil)
            (t (apply #'append (list l) (mapcar #' mapGetAllSublistsOfGivenList l)))
           )
)

(print (mapGetAllSublistsOfGivenList '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

; d) Write a function to transform a linear list into a set.

; math model
; linearListToSet(l1l2...ln) = () if n = 0, 
;                            = l1 + linearListToSet(l2...ln) if checkMemberOfList(l2...ln l1) is false
;                            = linearListToSet(l2...ln) otherwise;

(DEFUN linearListToSet (l)
        (COND
         ((null l) nil)
         ((not (checkMemberOfList (cdr l) (car l))) (append (list (car l)) (linearListToSet (cdr l))))
         (t (linearListToSet (cdr l)))
         )           
)

(print (linearListToSet '(1 2 1 3 2 1 5 4 2)))
