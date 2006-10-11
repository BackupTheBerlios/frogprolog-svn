:- foreign(/(myvar, 1), pl_my_var, mypred).

printme(testterm(A, B, C)) :- write(A), write(B), write(C), nl.
printme(A) :- write(A), myvar(B), nl.
