; 8. Return the list of nodes of a tree of type (2) accessed inorder.
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
; getInorderTraversal(t1t2t3...tn) = () if n = 0,
;                                  = appendTwoLists(getInorderTraversal(t2), appendTwoLists({t1}, getInorderTraversal(t3))) otherwise;

(DEFUN getInorderTraversal(l)
       (COND 
        ((null l) nil)
        (t (appendTwoLists (getInorderTraversal (cadr l)) (appendTwoLists (list (car l)) (getInorderTraversal (caddr l)))))
       )
)

(print (getInorderTraversal '(A (B) (C (D) (E)))))
