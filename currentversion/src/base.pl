:- dynamic(/('$instance', 1)).

findall(X, Goal, Xs) :-
   asserta('$instance'('$mark')), Goal,
   asserta('$instance'(X)), fail.

findall(X, Goal, Xs) :- 
   retract('$instance'(X1)), intern_reap_(X1, addVar([], Xs)), !.

intern_reap_(X, addVar(REST, Ys)) :-
   X \= '$mark', retract('$instance'(X1)), !,
   intern_reap_(X1, addVar([X|REST], Ys)).

intern_reap_('$mark', addVar(Xs, Xs)).


catch(ProtectedGoal, Pattern, Handler) :- ProtectedGoal.
on_exception(Pattern, ProtectedGoal, Handler) :- ProtectedGoal.
throw(Exception) :- write(Exception).
raise_exception(Exception) :- write(Exception).

%listen
member(X, [X|Xs]).
member(X, [Y|Ys]) :- member(X, Ys).

%prefix([], Ys).
%prefix([X|Xs]|[X|Ys]) :- prefix(Xs, Ys).

%suffix(Xs, Ys).
%suffix(Xs, [Y|Ys]) :- suffix(Xs, Ys).

append([], Ys, Ys).
append([X|Xs], Ys, [X|Zs]) :- append(Xs, Ys, Zs).

%sublist(Xs, Ys) :- prefix(Xs, Ys).
%sublist(Xs, [Y|Ys]) :- sublist(Xs, Ys).

reverse(Xs, Ys) :- reversein(Xs, [], Ys).
reversein([X|Xs], Acc, Ys) :- reversein(Xs, [X|Acc], Ys).
reversein([], Ys, Ys).

%length([], 0).
%length([X|Xs], N1) :- length(X, N), N1 is N+1.
