; 2.
; a) Write a function to return the product of two vectors.
; https://en.wikipedia.org/wiki/Dot_product

; math model
; productOfVectors(a1a2...an, b1b2...bn) = 0 if n = 0,
;                                        = a1 * b1 + productOfVectors(a2...an, b2...bn) otherwise;

(DEFUN productOfVectors (a b)
     (COND
      ((null a) 0)
      (t (+ (* (car a) (car b)) (productOfVectors (cdr a) (cdr b))))
     )
)

(print (productOfVectors '(1 3 -5) '(4 -2 -1)))


; b) Write a function to return the depth of a list. Example: the depth of a linear list is 1.

; math model
; getMax(a, b) = a if a > b,
;              = b otherwise;

(DEFUN getMax(a b)
        (COND
         ((> a b) a)
         (t b)
        )       
)

; math model
; getDepthOfList(l1l2...ln, x) = 0 if n = 0,
;                              = max(getDepthOfList(l1, x+1), getDepthOfList(l2...ln)) if l1 is a list,
;                              = getDepthOfList(l2...ln) otherwise;

(DEFUN getDepthOfList (l x)
        (COND
         ((null l) x)
         ((listp (car l)) (getMax (getDepthOfList (car l) (+ x 1)) (getDepthOfList (cdr l) x)))
         (t (getDepthOfList (cdr l) x))
        )
)

(DEFUN mainGetDepthOfList (l)
        (getDepthOfList l 1)
)

(print (mainGetDepthOfList '(4 (14 5) -2 (-1 3 (2 (4 6) 5) 23) 9)))


; c) Write a function to sort a linear list without keeping the double values.

; math model
; insertElementInListSorted(l1l2...ln, E) = (E) if n = 0, 
;                                         = l1l2...ln if E = l1,
;                                         = E + l1...ln if E < l1;
;                                         = l1 + insertElementInListSorted(l2...ln, E) otherwise;

(DEFUN insertElementInListSorted(l E)
        (COND
         ((null l) (list E))
         ((equal E (car l)) l)
         ((< E (car l)) (cons E l))
         (t (cons (car l) (insertElementInListSorted(cdr l) E)))
        )       
)

; math model
; sortElementWithoutDuplicates(l1l2...ln) = () if n = 0
;                                         = insertElementInListSorted(sortElementWithoutDuplicates(l2...ln), l1) otherwise;

(DEFUN sortElementWithoutDuplicates(l) 
        (COND
         ((null l) nil)
         (t (insertElementInListSorted (sortElementWithoutDuplicates (cdr l)) (car l)))
        )
)

(print (sortElementWithoutDuplicates '(1 6 8 34 0 32 9 3 1 2 4 6)))


; d) Write a function to return the intersection of two sets.

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
; intersectionOfTwoSets(a1a2...an, b1b2...bm) = () if n = 0,
;                                             = a1 + intersectionOfTwoSets(a2...an, b1b2...bm) if listContainsElement(b1b2...bm a1)
;                                             = intersectionOfTwoSets(a2...an, b1b2...bm) otherwise;


(DEFUN intersectionOfTwoSets(s1 s2)
        (COND
         ((null s1) nil)
         ((listContainsElement s2 (car s1)) (cons (car s1) (intersectionOfTwoSets (cdr s1) s2)))
         (t (intersectionOfTwoSets (cdr s1) s2))
        )
)

(print(intersectionOfTwoSets '(0 1 2 3 4 5) '(1 2 3) ))
(print(intersectionOfTwoSets '(0 1 2 3 4 5) '() ))
