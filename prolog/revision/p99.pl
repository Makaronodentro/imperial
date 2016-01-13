% 
% Solver: Makaronodentro
% Date: 5/1/2015
% Problem: http://www.ic.unicamp.br/~meidanis/courses/mc336/2009s2/prolog/problemas/
% 

% P1 Find the last element of a list.

my_last(X, [X]).
my_last(X, [_,H|T]) :-
    my_last(X, [H|T]).
    
% P2 Find the last but one element of a list.

my_prelast(X, [X,_]).
my_prelast(X, [_,H1,H2|T]) :-
    my_prelast(X, [H1,H2|T]).
    
% P3 Find the Kth element of a list

element_at(X, L, N) :-
    N1 is N - 1,
    length(T, N1),
    append(T, [X|_], L).

% P4 Find the length

my_length([], 0).
my_length([_|T], N) :-
    my_length(T, NNew),
    N is NNew + 1.
    
% P5 Reverse a list

rev(L, R) :-
    rev(L, [], R).
    
rev([], R, R).
rev([H|T], Acc, R) :-
    rev(T, [H|Acc], R).
    
% P6 palindrome?

palin(L) :-
    rev(L, L).

% P7 Flatten a list of lists
my_flatten([], []) :- !.
my_flatten([H|T], X) :-
    !,
    my_flatten(H, H_New),
    my_flatten(T, T_New),
    append(H_New, T_New, X).
my_flatten(L, [L]).

% Tail recursive
my_flatten2(L, X) :-
    my_flatten2(L, [], X).

my_flatten2([], Acc, Acc).
my_flatten2([L|Ls], Acc, X) :-
    (
        is_list(L)
        ->
            my_flatten2(L, L1),
            append(Acc, L1, NewAcc),
            my_flatten2(Ls, NewAcc, X)
        ;
            append(Acc, [L], NewAcc),
            my_flatten2(Ls, NewAcc, X)
    ).
    
% P8 Eliminate consecutive duplicates of a list
    
compress([X], [X]).
compress([H,H|T], X) :-
    compress([H|T], X).
compress([H,H1|T], [H|X]) :-
    H \= H1,
    compress([H1|T], X).

% P9 Pack consecutive duplicates into sublists

pack(L, X) :-
    pack(L, [], X).
    
pack([X,X], Sub, R) :-
    append(Sub, [X,X], NewSub),
    R = [NewSub].

pack([X,Y], Sub, R) :-
    X \= Y,
    append(Sub, [X], NewSub),
    R = [NewSub|[[Y]]].

pack([H,H,Z|T], Sub, X) :-
    append(Sub, [H], NewSub),
    pack([H,Z|T], NewSub, X).
    
pack([H,H1,Z|T], Sub, [NewSub|X]) :-
    H \= H1,
    append(Sub, [H], NewSub),
    pack([H1,Z|T], [], X).

% P10 Run-Length encoding of a list

encode(L, R) :-
    pack(L, P),
    encode(P, [], R).
    
encode([], A, A).
encode([H|T], Acc, R) :-
    length(H, X),
    [Y|_] = H,
    append(Acc, [[X, Y]], NewAcc),
    encode(T, NewAcc, R).

% P11 Modified run-length encoding
    
encode_modified(L, R) :-
    pack(L, P),
    encode_modified(P, [], R).
    
encode_modified([], A, A).
encode_modified([H|T], Acc, R) :-
    length(H, X),
    [Y|_] = H,
    (
        X \= 1
        ->
            append(Acc, [[X, Y]], NewAcc),
            encode_modified(T, NewAcc, R)
        ;
            append(Acc, [Y], NewAcc),
            encode_modified(T, NewAcc, R)
    ).

% P12 Decode a run-length list
decode(L, R) :-
    decode(L, [], R).
    
decode([], A, A).
decode([H|T], A, R) :-
    getSub(H, X),
    append(A, X, NewA),
    decode(T, NewA, R).
    
getSub([_, 0], []).
getSub([X, N], [X|L]) :-
    N > 0,
    NNew is N - 1,
    getSub([X, NNew], L).
    
% P13 Run-length encoding of a list, (direct-solution).

encode_direct(L, R) :-
    encode_direct(L, 1, [], R).

encode_direct([H], N, A, R) :-
    append(A, [[H, N]], R).

encode_direct([H,H|T], N, A, R) :-
    NNew is N + 1,
    encode_direct([H|T], NNew, A, R).
encode_direct([H,H1|T], N, A, R) :-
    H \= H1,
    append(A, [[H,N]], NewA),
    encode_direct([H1|T], 1, NewA, R).

% P14 Duplicate all elements of a list

dupli([], []).
dupli([H|T], [H,H|R]) :-
    dupli(T, R).

% P15

dupli(L, N, R) :-
    dupli(L, N, R, N).
    
dupli([],_,[],_).
dupli([_|T],N,R,0) :- 
    dupli(T,N,R,N).
dupli([H|T],N,[H|R],K) :- K > 0, K1 is K - 1, dupli([H|T],N,R,K1).

% P16 NOT DONE

drop(L1,N,L2) :- drop(L1,N,L2,N).
 
drop([],_,[],_).
drop([_|Xs],N,Ys,1) :- 
    drop(Xs,N,Ys,N).
    
drop([X|Xs],N,[X|Ys],K) :- 
    K > 1, 
    K1 is K - 1, 
    drop(Xs,N,Ys,K1).
    
% P17

split(L, N, L1, L2) :-
    length(L1, N),
    append(L1, L2, L).
    
% P18

slice(L, N, M, R) :-
    NNew is N - 1,
    MNew is M - NNew,
    length(X, NNew),
    append(X, Y, L),
    length(R, MNew),
    append(R, _, Y).
    

% P19 Rotate a list N places to the left.

rotate(L, N, R) :-
    length(L, Length),
    T is Length + N,
    T1 is mod(T, Length),
    length(X, T1),
    append(X, Y, L),
    append(Y, X, R).

% P20 Remove the K'th element from a list.

% remove_at(X,[a,b,c,d],2,R).

remove_at(H, L, N, R) :-
    NNew is N - 1,
    length(X, NNew),
    append(X, [H|Y], L),
    append(X,Y,R).

% P21 Insert an element at a given position into a list.

% insert_at(alfa,[a,b,c,d],2,L).

insert_at(H, L, N, R) :-
    length(L, Length),
    T is Length + N - 1,
    T1 is mod(T, Length),
    length(X, T1),
    append(X, Y, L),
    append(X, [H|Y], R).

% P22 Create a list containing all integers within a given range.

range(X,Y,L) :-
    range(X,Y,[],L).
    
range(X,X,A,R) :-
    append(A, [X], R).
range(X,Y,A,R) :-
    Y > X,
    NewX is X + 1,
    append(A, [X], NewA),
    range(NewX, Y, NewA, R).
    
% P23 Extract a given number of randomly selected elements from a list.

% ?- rnd_select([a,b,c,d,e,f,g,h],3,L).
% L = [e,d,a]

rnd_select(_, 0, []).
rnd_select(L, N, [H|R]) :-
    N > 0,
    length(L, X),
    I is random(X) + 1,
    remove_at(H, L, I, NewL),
    NewN is N - 1,
    rnd_select(NewL, NewN, R).
    

% P24 Lotto: Draw N different random numbers from the set 1..M.

% ?- lotto(6,49,L).
% L = [23,1,17,33,21,37]

lotto(N, M, R) :-
    N > 0,
    M > 0,
    M >= N,
    range(1,M,L),
    rnd_select(L,N,R).
    

% P25 Generate a random permutation of the elements of a list.

% ?- rnd_permu([a,b,c,d,e,f],L).
% L = [b,a,d,c,e,f]

rnd_permu(L, R) :-
    length(L, X),
    rnd_select(L, X, R).

% P26 Generate the combinations of K distinct objects chosen from the N elements of a list

% ?- combination(3,[a,b,c,d,e,f],L).
% L = [a,b,c] ;
% L = [a,b,d] ;
% L = [a,b,e] ;
% ...

combination(0,_,[]).
combination(N,L,[X|R]) :-
    member(X,L),
    remove_el(L, [X], NewL),
    NewN is N - 1,
    combination(NewN, NewL, R).

remove_el([], _, []).
remove_el([H|T], X, R) :-
    (
        member(H, X)
        ->
            remove_el(T, X, R)
        ;
            remove_el(T, X, NewR),
            R = [H|NewR]
            
    ).
% P27 Group the elements of a set into disjoint subsets

% a)

% ?- group3([aldo,beat,carla,david,evi,flip,gary,hugo,ida],G1,G2,G3).
% G1 = [aldo,beat], G2 = [carla,david,evi], G3 = [flip,gary,hugo,ida]

group3(L, G1, G2, G3) :-
    length(L, 9),
    combination(2, L, G1),
    remove_el(L, G1, L1),
    combination(3, L1, G2),
    remove_el(L1, G2, L2),
    combination(4, L2, G3).

% b)

% group([aldo,beat,carla,david,evi,flip,gary,hugo,ida],[2,2,5],Gs).
% Gs = [[aldo,beat],[carla,david],[evi,flip,gary,hugo,ida]]
% ...

group([],[],[]).
group(L, [N|Ns], [G|Gs]) :-
    sumof([N|Ns], Length), % get implied length
    length(L, Length), % verify length
    select_els(N, L, G), % select N elements from L
    remove_el(L, G, L1),
    group(L1, Ns, Gs).
    
    
select_els(0, _, []).
select_els(N, L, [X|R]) :-
    N1 is N - 1,
    el(X, L, L1), % el, unlike member cannot reselect an element
    select_els(N1, L1, R).

el(X, [X|L], L).  
el(X, [_|T], L) :- el(X, T, L). % if the previous call fails, skip an el.

sumof([], 0).
sumof([H|T], R) :-
    sumof(T, NewR),
    R is NewR + H.

% P28 Sorting a list of lists according to length of sublists

% a)

% ?- lsort([[a,b,c],[d,e],[f,g,h],[d,e],[i,j,k,l],[m,n],[o]],L).
% L = [[o], [d, e], [d, e], [m, n], [a, b, c], [f, g, h], [i, j, k, l]]

lsort([H], [H]).
lsort(L, [H|R]) :-
    getShortest(L, H),
    remove_H(L, H, L1),
    lsort(L1, R).
    

getShortest([H], H).
getShortest([H|T], R) :-
    getShortest(T, L),
    length(H, X),
    length(L, Y),
    (
        X =< Y
        ->
            R = H
        ;
            R = L
    ).
    
remove_H([H|T], H, T) :- !.
remove_H([H|T], X, [H|R]) :- remove_H(T, X, R).

% b)

% ?- lfsort([[a,b,c],[d,e],[f,g,h],[d,e],[i,j,k,l],[m,n],[o]],L).
% L = [[i, j, k, l], [o], [a, b, c], [f, g, h], [d, e], [d, e], [m, n]]

lfsort([H], [H]).
lfsort(L, [H|R]) :-
    getLeastFrequent(L, H),
    remove_H(L, H, L1),
    lfsort(L1, R).
    
getLeastFrequent(L, R) :-
    getLeastFrequent(L, L, 0, R).
    
getLeastFrequent([H], L, N, [H]) :-
    length(H, Length),
    countLengthOccurences(L, Length, N).
    
getLeastFrequent([H|T], L, N, R) :-
    length(H, Length),
    countLengthOccurences([H|T], Length, X),
    getLeastFrequent(T, L, CurrN, CurrR),
    (
        CurrN < X
        ->
            R = H,
            N = Length
        ;
            R = CurrR,
            N = CurrN
    ).

countLengthOccurences([], _, 0).
countLengthOccurences([H|T], L, X) :-
    countLengthOccurences(T, L, OldX),
    (
        length(H, L)
        ->
            X is OldX + 1
        ;
            X is OldX
    ).

bsort(L,S) :- bsort(L, [], S).
bsort([], A, A).
bsort([H|T], A, S) :-
    bubble(H, T, NT, Max),
    bsort(NT, [Max|A], S).
    
bubble(X, [], [], X).
bubble(X, [Y|T], [Y|NT], Max) :- X > Y, bubble(X, T, NT, Max).
bubble(X, [Y|T], [X|NT], Max) :- X =< Y, bubble(Y, T, NT, Max).

flatten3(L,F) :- flatten3(L,[],F).

flatten3([], A, A).
flatten3([H|T], A, F) :-
    (
        is_list(H)
        ->
            flatten3(H, H1),
            append(A, H1, NA),
            flatten3(T, NA, F)
        ;
            append(A, [H], NA),
            flatten3(T, NA, F)
    ).