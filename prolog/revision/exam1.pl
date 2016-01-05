% Prolog Exam Practice

% 1 subList(L1, L2) | every element in list L1 is also in list L2

% Call if L1 has length 1, and X is a member of L2, return true
subList([X],L2):-
    member(X,L2),!.

% Call if L1 has length > 1
subList([H|T], L2) :-
    member(H, L2),!, % check if H is a member of L2
    subList(T, L2). % recursively check the rest of the list
    
% 2 difference(L1, L2, L) | L consists of all X in(X, L1), \+in(X, L2)

% Call if L1 is empty - then L will be empty (base case).
difference([], _, []).

% Call if L1 is not empty
difference([H|T], L2, [H|L]) :- % place H in the front of L
    \+member(H, L2), % if H is not a member of L2
    difference(T, L2, L). % recursively check the rest of the list

% Call if L1 is not empty & H is a member of L2
difference([H|T], L2, L) :-
    member(H, L2), % if this is not included this call is not mutually exclusive to the previous
    difference(T, L2, L). % simply discard H


% 3 sift(L, N, Result) | Result is L without occurences > N

% Call if L is empty - then result is empty 
sift([], _, []).

% Call if L is not empty
sift([H|T], N, [H|R]) :- % place H in the front of L, if ->
    H =< N,
    sift(T, N, R). % check the rest of the list 

% Call if L is not empty and H was not =< N
sift([H|T], N, Result) :-  
    H > N, % only in this case you should discard H
    sift(T, N, Result). % simply discard H
    
% 4 common(L1, L2, I).

% Call always - will fail if there are no common members
common(L1, L2, L) :-
    setof(X, (member(X,L1),member(X,L2)), L).

% Call only if first call fails
common(L1, L2, L) :-
    \+setof(X, (member(X,L1),member(X,L2)), L), % only in this case L = []
    L = []. % return an empty list
    
% 5 delete(L, Result) | Result is list L with every other element deleted.

% Call when L has 1 element left in it (base case). Return false if empty.
delete([X],[X]). % Copy the single element into the Result.

% Call if L has 2 elements (base case 2).
delete([H,_], [H]). % Discard the second and copy the first into Result

% Call for every other case
delete([H1,_|T], [H1|R]) :- % Place the first element in Result, discard 2nd
    delete(T, R). % Recursively call the rest of the list
    
% 6 process(L1, L2, Consistent Inconsistent).

process(_, [], [], []).

process(L1, [(N,A,S)|T2], [(N,A,S)|T3], I) :-
    member((N,A), L1),
    process(L1, T2, T3, I).

process(L1, [(N,A,S)|T2], C, [(N,A,S)|T4]) :-
    \+member((N,A), L1),
    process(L1, T2, C, T4).
    
% 7 split(L, N, L1, L2)

split([], _, [], []).

split([H|T], N, [H|L1], L2) :-
    N > 0,
    New is N - 1,
    split(T, New, L1, L2).
    
split([H|T], N, L1, [H|L2]) :-
    N = 0,
    split(T, N, L1, L2).
    
% 8 drop(L, N, Result) | Drop every N'th element from a list L.

drop(L, N, Result) :-
    drop(L, Result, N, N).

drop([], [], _, _).

drop([_|T], R, N, NLeft) :-
    NLeft = 1,
    drop(T, R, N, N).
    

drop([H|T], [H|R], N, NLeft) :-
    NLeft > 1,
    New is NLeft - 1,
    drop(T, R, N, New).
    
drop1(L, N, []) :-
    length(L, X),
    X < N.

drop1(L, N, Result) :-
    Y is N - 1,
    length(X, Y),
    append(X, [_|T], L),
    drop1(T, N, NewResult),
    append(X, NewResult, Result).
    
% 9 enrollment(L, Student, Degree).

enrollment([(_,LS)|T], S, D) :-
    \+member(S, LS),
    enrollment(T, S, D).

enrollment([(D,LS)|_], S, D) :-
    member(S, LS).
    
% 10 student_list(L, Meng, MSc).

student_list([], [], []).

student_list([(meng,LS)|T], Meng, MSc) :-
    student_list(T, MengNew, MSc),
    append(LS, MengNew, Meng).
    
student_list([(msc,LS)|T], Meng, MSc) :-
    student_list(T, Meng, MScNew),
    append(LS, MScNew, MSc).