; 5.
; a) Write twice the n-th element of a linear list. Example: for (10 20 30 40 50) and n=3 will produce (10 20 30 30 40 50).

; math model
; doubleNthElement(l1l2...ln, c, N) = {} if n = 0,
;                                   = {l1, l1} U l2...ln if c = N,
;                                   = {l1} U doubleNthElement(l2...ln, c + 1, N), otherwise;

(DEFUN doubleNthElement(l c N) 
        (COND
         ((null l) nil)
         ((equal c N) (cons (car l) (cons (car l) (cdr l))))
         (t (cons (car l) (doubleNthElement (cdr l) (+ c 1) N)))
        )
)

(DEFUN mainDoubleNthElement (l N)
        (doubleNthElement l 1 N)
)

(print(mainDoubleNthElement '(1 2 3 5 6) 1))


; b) Write a function to return an association list with the two lists given as parameters.
; Example: (A B C) (X Y Z) --> ((A.X) (B.Y) (C.Z)).

; math model
; associateLists(a1a2...an, b1b2...bm) = 
(DEFUN associateLists(a b)
        (COND
         ((or (null a) (null b)) nil)
         (t (cons (cons (car a) (car b)) (associateLists (cdr a) (cdr b))))
        )
)

(print (associateLists '(a b c) '(x y z)))


; c) Write a function to determine the number of all sublists of a given list, on any level.
; A sublist is either the list itself, or any element that is a list, at any level. Example:
; (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 lists:
; (list itself, (3 ...), (4 5), (6 7), (9 10)).

; math model
; getDepthOfList(l1l2...ln) = 1 if n = 0,
;                           = 1 + getDepthOfList(l1) + getDepthOfList(l2...ln) if l1 is list,
;                           = getDepthOfList(l2...ln) otherwise;

(DEFUN getDepthOfList(l)
      (COND
       ((null l) 1)
       ((listp (car l)) (+ (getDepthOfList (car l)) (getDepthOfList (cdr l))))
       (t (getDepthOfList (cdr l)))
      )
)

(print (getDepthOfList '(1 2 (3 (4 5) (6 7)) 8 (9 10))))


; d) Write a function to return the number of all numerical atoms in a list at superficial level.

; math model
; getNumberOfNumericalAtoms(l1l2...ln) = 0 if n = 0, 
;                                      = 1 + getNumberOfNumericalAtoms(l2...ln) if l1 is atom,
;                                      = getNumberOfNumericalAtoms(l2...ln) otherwise;

(DEFUN getNumberOfNumericalAtoms(l)
        (COND
         ((null l) 0)
         ((numberp (car l)) (+ 1 (getNumberOfNumericalAtoms (cdr l))))
         (t (getNumberOfNumericalAtoms (cdr l)))
        )
)

(print (getNumberOfNumericalAtoms '(a 1 2 d c 5 1 s -1)))
