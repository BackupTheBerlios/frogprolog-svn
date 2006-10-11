edge(a,b).
edge(a,c).
edge(b, d).
edge(c, d).
edge(d,e).
edge(f, g).

connected(Node, Node).
connected(Node1, Node2) :- edge(Node1, Link), connected(Link, Node2).

sayyesno(Command) :- Command, !, write(true),write(': '), write(Command),nl.
sayyesno(Command) :- write(no), nl.

init :- sayyesno(connected(a, b)),
        sayyesno(connected(a,c)),
        sayyesno(connected(a, d)),
        sayyesno(connected(a, e)), 
        sayyesno(connected(a, g)),
        ( 
           connected(a, X), write(X), nl, fail
           ;
           true
        ).