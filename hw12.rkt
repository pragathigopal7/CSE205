;Question 1: Ackernmann Function(recursive procedure)
(define (Ackermann s t) ;this statement calculates the size-n problem
  (cond
        ((= s 0) (+ t 1)) ; Provides the stopping condition as well as the return value
        ((= t 0) (Ackermann (- s 1) 1)) ; statement for a size-m problem
        (else (Ackermann (- s 1) (Ackermann s (- t 1)))))) ; size-m problems

;Question 2: creates a list with alternative values from the 3 given lists
(define (alternate lst1 lst2 lst3) ; size-n problem
  (if (null? lst1) ; following lines from size-(n-1) to size n problem 
      (append lst1 lst2 lst3) ; stopping condition 
      (append (list (car lst1) (car lst2) (car lst3)) (alternate (cdr lst1) (cdr lst2) (cdr lst3))))) ; size-m problems


;Question 3: shuffle lists one and two in pairs
(define (pairs lst1 lst2) ; size-n problem
  (if (null? lst1) ; the following lines: from size-(n-1) to size-n problems
      '() ; stopping condition
      (append (list (cons (car lst1) (car lst2))) (pairs (cdr lst1) (cdr lst2))))) ; size-m problems

;Question 4: gives the sum of all the odd numbers in the list
 (define (sumOdds lst) ;size-n problem
  (cond ; all the following lines: from size-(n-1) problems to size-n problem
        ((null? lst) 0 )            ; stopping condition
        ((odd? (car lst) )          ; if the first element is odd
         (+ (car lst) (sumOdds (cdr lst)))) ; then add one and advance recursion
        ((even? (car lst))                 ; otherwise
         (sumOdds (cdr lst)))))       ; size-m prolbems

((lambda (lst)  ;size-n problem
   (cond  ; all the following lines: from size-(n-1) problems to size-n problem
        ((null? lst) 0 )            ; stopping condition
        ((odd? (car lst) )          ; if the first element is odd
         (+ (car lst) (sumOdds (cdr lst)))) ; then add one and advance recursion
        ((even? (car lst))                 ; otherwise
         (sumOdds (cdr lst))))) ;size-m problems
     '(1 3 4 5 6 -7))

;Question 5 gives the maximum number of the list
(define (findMax lst)  ;size-n problem
  (cond ; all the following lines: from size-(n-1) to size-n problem
    ((null? lst) (error "Empty list"))
    ((= (length lst) 1) (car lst))
    ((> (car lst) (findMax (cdr lst))) (car lst))
    (else (findMax (cdr lst))))) ; size-m problems