; 12. Determine the list of nodes accesed in preorder in a tree of type (2).
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
; getPreorderTraversal(t1t2t3...tn) = () if n = 0,
;                                    = appendTwoLists({t1}, appendTwoLists(getPreorderTraversal(t2), getPreorderTraversal(t3))) otherwise;

(DEFUN getPreorderTraversal(l)
       (COND 
        ((null l) nil)
        (t (appendTwoLists (list (car l)) (appendTwoLists (getPreorderTraversal (cadr l)) (getPreorderTraversal (caddr l)))))
       )
)

(print (getPreorderTraversal '(A (B) (C (D) (E)))))
