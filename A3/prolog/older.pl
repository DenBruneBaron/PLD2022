older(a.b).
older(b.c).
older(c.d).
older(d.X).
older(X,Z) :- older(X.Y), older(Y,Z).


