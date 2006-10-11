p(X) :- q(X, Y), write(Y). 
q(V, U) :- r(U, V). 
r(a, b).

init :- 
   p(X), write(X), nl.