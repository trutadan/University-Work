; 15.
; a) Write a function to insert an element E on the n-th position of a linear list.

; math model
; insertElementOnNthElement(l1l2...ln, N, E) = () if n = 0, 
;                                            = {E} U l1l2...ln if N = 1,
;                                            = {l1} U insertElementOnNthElement(l2...ln, N - 1, E) otherwise;

(DEFUN insertElementOnNthElement(l N E)
        (COND
         ((null l) nil)
         ((equal 1 N) (cons E l))
         (t (cons (car l) (insertElementOnNthElement (cdr l) (- N 1) E)))
        )
)

(print (insertElementOnNthElement '(1 2 a b 3) 4 9))


; b) Write a function to return the sum of all numerical atoms of a list, at any level.

; math model
; getSumOfNumericalAtoms(l1l2...ln) = 0 if n = 0, 
;                                   = l1 + getSumOfNumericalAtoms(l2...ln) if l1 is a number,
;                                   = getSumOfNumericalAtoms(l2...ln) otherwise;

(DEFUN getSumOfNumericalAtoms(l)
        (COND
         ((null l) 0)
         ((numberp (car l)) (+ (car l) (getSumOfNumericalAtoms (cdr l))))
         (t (getSumOfNumericalAtoms (cdr l)))
        )
)

(print (getSumOfNumericalAtoms '(1 a 2 b 3 c 4)))


; c) Write a function to return the set of all sublists of a given linear list. Ex. For list ((1 2 3) ((4 5) 6)) => ((1 2 3) (4 5) ((4 5) 6))

; math model
; getAllSublistsOfList(l1l2...ln) = () if n = 0,
;                                 = l1 U getAllSublistsOfList(l1) U getAllSublistsOfList(l2...ln) if l1 is list,
;                                 = getAllSublistsOfList(l2...ln) otherwise;

(DEFUN getAllSublistsOfList(l)
        (COND
         ((null l) nil)
         ((listp (car l)) (append (list (car l))  (getAllSublistsOfList (car l)) (getAllSublistsOfList (cdr l))))
         (t (getAllSublistsOfList (cdr l)))
        )
)

(print (getAllSublistsOfList '((1 2 3) ((4 5) 6))))

; d) Write a function to test the equality of two sets, without using the difference of two sets.

; math model
; listContainsElement(l1l2...ln, E) = false if n = 0,
;                                   = true if l1 = E,
;                                   = listContainsElement(l2...ln, E) otherwise;

(DEFUN listContainsElement(l E)
         (COND
          ((null l) nil)
          ((equal (car l) E) t)
          (t (listContainsElement (cdr l) E))
         )
)

; math model
; testEqualityOfTwoSets(a1a2...an, b1b2...bm) = true if n = 0
;                                             = false if not listContainsElement(b1b2...bm, a1),
;                                             = testEqualityOfTwoSets(a2...an, b1b2...bm) otherwise;
       
(DEFUN testEqualityOfTwoSets(s1 s2)
         (COND
          ((null s1) t)
          ((not (listContainsElement s2 (car s1))) nil)
          (t (testEqualityOfTwoSets (cdr s1) s2))
         )
)
       
(DEFUN mainTestEqualityOfTwoSets(s1 s2)
        (and (testEqualityOfTwoSets s1 s2) (testEqualityOfTwoSets s2 s1))
)
       
(print (mainTestEqualityOfTwoSets '(1 2 6 3) '(1 6 2 3)))