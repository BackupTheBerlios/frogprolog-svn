init :- =(A,4), write(4), write('='), write(A), nl,
        =(B,4.5), write(4.5), write('='), write(B), nl,
        =(C,atom), write(atom), write('='), write(C), nl,
        =(D,str(atom, 4, 4.5)), write(str(atom, 4, 4.5)), write('='), write(D), nl,
        =(test(X, t2(elch)), Y), =(Y,test(ok, Z)), =(Z,t2(W)),
        write('W = '), write(W), nl,
        write('X = '), write(X), nl,
        write('Y = '), write(Y), nl,
        write('Z = '), write(Z), nl.
