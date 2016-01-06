subList([X], L2) :-
    member(X, L2),!.
    
subList([H|T], L2) :-
    member(H, L2),!,
    subList(T, L2).
    
% 2

% Note if L1 is empty I decided it should fail
difference([H|T], L2, L) :-
    difference([H|T], L2, [], L).

difference([], _, Acc, Acc).
difference([H|T], L2, Acc, L) :-
    (
        member(H, L2)
        ->
        difference(T, L2, Acc, L)
        ;
        difference(T, L2, [H|Acc], L)
    ).
    
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

common(L1, L2, I) :-
    setof(X, (member(X, L1), member(X, L2)), I).
    
common(L1, L2, I) :-
    \+setof(X, (member(X, L1), member(X, L2)), I),
    I = [].
    
delete([], []).
delete([X], [X]) :- !.
delete([H,_|T], [H|R]) :-
    delete(T, R).
    
process(_, [], [], []).
process(L1, [(N,A,S)|T], [(N,A,S)|C], I) :-
    member((N,A), L1),
    process(L1, T, C, I).
process(L1, [(N,A,S)|T], C, I) :-
    \+member((N,A), L1),
    process(L1, T, C, NewI),
    append(NewI, [(N,A,S)], I).
    
split(L, N, L1, L2) :-
    length(L1, N),
    append(L1, L2, L).
    
drop(L, N, L) :-
    length(L, X),
    X < N.

drop(L, N, R) :-
    X is N - 1,
    length(RFront, X),
    append(RFront, [_|Rest], L),
    drop(Rest, N, RNew),
    append(RFront, RNew, R).

enrollment(L, Student, Degree) :-
    member((Degree,SL), L),
    member(Student, SL).
    
student_list([], [], []).
student_list([(meng,LS)|T], Meng, MSc) :-
    student_list(T, NewMeng, MSc),
    append(LS, NewMeng, Meng).
student_list([(msc,LS)|T], Meng, MSc) :-
    student_list(T, Meng, NewMSc),
    append(LS, NewMSc, MSc).
    