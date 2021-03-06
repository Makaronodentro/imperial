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
    difference_proc([], _, []).
    
    % Call if L1 is not empty
    difference_proc([H|T], L2, [H|L]) :- % place H in the front of L
        \+member(H, L2), % if H is not a member of L2
        difference_proc(T, L2, L). % recursively check the rest of the list
    
    % Call if L1 is not empty & H is a member of L2
    difference_proc([H|T], L2, L) :-
        member(H, L2), % if this is not included this call is not mutually 
        % exclusive to the previous
        difference_proc(T, L2, L). % simply discard H

    % Tail recursive version
    difference(L1, L2, L) :-
        difference(L1, L2, [], L).
    
    difference([], _, Acc, Acc).
    difference([H|T], L2, Acc, L) :-
        (
            member(H, L2)
            ->
            difference(T, L2, Acc, L)
            ;
            difference(T, L2, [H|Acc], L)
        ).


% 3 sift(L, N, Result) | Result is L without occurences > N

    % Call if L is empty - then result is empty 
    sift1([], _, []).
    
    % Call if L is not empty
    sift1([H|T], N, [H|R]) :- % place H in the front of L, if ->
        H =< N,
        sift1(T, N, R). % check the rest of the list 
    
    % Call if L is not empty and H was not =< N
    sift1([H|T], N, Result) :-  
        H > N, % only in this case you should discard H
        sift1(T, N, Result). % simply discard H
    
    % Tail recursive.
    sift(L, N, Result) :-
    sift(L, N, [], Result).

    sift([], _, Acc, Acc).
    sift([H|T], N, Acc, Result) :-
        (
            H > N
            ->
            sift(T, N, Acc, Result)
            ;
            append(Acc, [H], NewAcc),
            sift(T, N, NewAcc, Result)
        ).
    
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

    split(L, N, L1, L2) :-
        length(L1, N),
        append(L1, L2, L).
    
    split_proc([], _, [], []).
    
    split_proc([H|T], N, [H|L1], L2) :-
        N > 0,
        New is N - 1,
        split_proc(T, New, L1, L2).
        
    split_proc([H|T], N, L1, [H|L2]) :-
        N = 0,
        split_proc(T, N, L1, L2).
    
% 8 drop(L, N, Result) | Drop every N'th element from a list L.

    drop(L, N, Result) :-
        drop(L, N, N, [], Result).
    
    drop([], _,_, RAcc, RAcc).
    drop([H|T], N, NAcc, RAcc, R) :-
        (
            NAcc = 1
            ->
            drop(T, N, N, RAcc, R)
            ;
            NLeft is NAcc - 1,
            append(RAcc, [H], NewR),
            drop(T, N, NLeft, NewR, R)
        ).
        
    drop1(L, N, L) :-
        length(L, X),
        X < N.
    
    drop1(L, N, Result) :-
        Y is N - 1,
        length(X, Y),
        append(X, [_|T], L),
        drop1(T, N, NewResult),
        append(X, NewResult, Result).
    
% 9 enrollment(L, Student, Degree).

    enrollment(L, S, D) :-
        member((D,SL), L),
        member(S, SL).
    
% 10 student_list(L, Meng, MSc).

    student_list([], [], []).
    
    student_list([(meng,LS)|T], Meng, MSc) :-
        student_list(T, MengNew, MSc),
        append(LS, MengNew, Meng).
        
    student_list([(msc,LS)|T], Meng, MSc) :-
        student_list(T, Meng, MScNew),
        append(LS, MScNew, MSc).