; 4.
; a) Write a function to return the sum of two vectors.

; math model
; getSumOfTwoVectors (l1l2...ln, p1p2...pm) = p1p2...pm, if n = 0 
;                                           = {l1 + p1} U getSumOfTwoVectors(l2...ln, p2...pm), otherwise;

(DEFUN getSumOfTwoVectors (a b)
    (COND 
     ((or (null a) (null b)) nil)
     (t (cons (+ (car a) (car b)) (getSumOfTwoVectors (cdr a) (cdr b))))
    )
)

(print (getSumOfTwoVectors '(1 2 3) '(4 5 6 19)))


; b) Write a function to get from a given list the list of all atoms, on any
;  level, but on the same order. Example:
;  (((A B) C) (D E)) ==> (A B C D E)

; math model
; appendTwoListsToLinearList(l1l2...ln, p1p2...pm) = p1p2...pm, if n = 0
;                                                  = {l1} U appendTwoListsToLinearList(l2...ln, p1p2...pm), otherwise;

(DEFUN appendTwoListsToLinearList (a b)
    (COND 
     ((null a) b)
     (t (cons (car a) (appendTwoListsToLinearList (cdr a) b)))
    )
)

; math model
; liniarizeList(l1l2...ln) = NIL, if n = 0
;                          = appendTwoListsToLinearList(liniarizeList(l1), liniarizeList(l2...ln)), if l1 is a list
;                          = appendTwoListsToLinearList((list(l1), liniarizeList(l2...ln)), otherwise
       
(DEFUN liniarizeList (l)
    (COND
     ((null l) nil)
     ((listp (car l)) (appendTwoListsToLinearList (liniarizeList (car l)) (liniarizeList (cdr l))))
     (t (cons (car l) (liniarizeList (cdr l))))
    )
)

(print (liniarizeList '(((A B) C) (D E))))


; c) Write a function that, with a list given as parameter, inverts only continuous
;  sequences of atoms. Example:
;  (a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))

; math model
; reverseLinearList(l1l2...ln) = NIL , if n = 0
;                              = appendTwoListsToLinearList(reverseLinearList(l2...ln), reverseLinearList(l1)), if l1 is a list
;                              = appendTwoListsToLinearList(reverseLinearList(l2...ln), list(l1)), otherwise

(DEFUN reverseLinearList (l)
    (COND 
     ((null l) nil)
     (t (appendTwoListsToLinearList (reverseLinearList (cdr l)) (list (car l)))) 
    )        
)

; math model
; invertContinuousSequencesOfAtoms(l1l2...ln, aux) = aux, if n = 0
;                                                  = appendTwoListsToLinearList(aux, appendTwoListsToLinearList(list(invertCont(l1, NIL)), invertContinuousSequencesOfAtoms(l2...ln, NIL))), if l1 is a list
;                                                  = invertContinuousSequencesOfAtoms(l2...ln, appendTwoListsToLinearList(list(l1), aux)), otherwise;

(DEFUN invertContinuousSequencesOfAtoms (l aux)
    (COND
        ((null l) (reverseLinearList aux))
        ((listp (car l)) (appendTwoListsToLinearList (reverseLinearList aux) (cons (invertContinuousSequencesOfAtoms (car l) nil) (invertContinuousSequencesOfAtoms (cdr l) nil))))
        (T (invertContinuousSequencesOfAtoms (cdr l) (appendTwoListsToLinearList aux (list (car l)))))
    )
)

(print (invertContinuousSequencesOfAtoms '(a b c (d (e f) g h i)) nil))


; d) Write a list to return the maximum value of the numerical atoms from a list, at superficial level.

; math model
; getMaxOfTwoNumbers(a,b) = a, if b is not a number
;                         = b, if a is not a number
;                         = a, if a > b
;                         = b, otherwise;

(defun getMaxOfTwoNumbers (a b)
    (cond
        ((and (not (numberp a)) (not (numberp b))) nil)
        ((not (numberp a)) b)
        ((not (numberp b)) a)
        ((> a b) a)
        (T b)
    )
)

; math model
; getMaximumValueOfList(l1l2...ln) = (), if n = 0
;                                  = getMaxOfTwoNumbers(l1, getMaximumValueOfList(l2...ln)), otherwise

(defun getMaximumValueOfList (l)
    (if (null (cdr l)) 
        (car l)
        (getMaxOfTwoNumbers (car l) (getMaximumValueOfList (cdr l)))
    )
)

(print (getMaximumValueOfList '(A 1 B 4 5 3 C F)))