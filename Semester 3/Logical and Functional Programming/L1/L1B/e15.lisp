; 15. Determine the list of nodes accesed in postorder in a tree of type (2).
; (A (B) (C (D) (E))) -> tree of type (2)

; math model 
; appendTwoListsToLinearList(a1a2...an, b1b2...bm) = b1b2...bm if n = 0,
;                                                  = {a1} U appendTwoListsToLinearList(a2...an, b1b2...bm) otherwise;

(DEFUN appendTwoLists(l1 l2)
        (COND
         ((null l1) l2)
         (t (cons (car l1) (appendTwoLists (cdr l1) l2)))
        )
)

; math model
; getPostorderTraversal(t1t2t3...tn) = () if n = 0,
;                                    = appendTwoLists(getPostorderTraversal(t2), appendTwoLists(getPostorderTraversal(t3), {t1})) otherwise;

(DEFUN getPostorderTraversal(l)
       (COND 
        ((null l) nil)
        (t (appendTwoLists (getPostorderTraversal (cadr l)) (appendTwoLists (getPostorderTraversal (caddr l)) (list (car l)))))
       )
)

(print (getPostorderTraversal '(A (B) (C (D) (E)))))
