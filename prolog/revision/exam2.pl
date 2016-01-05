% 1 last(List, X). | X is the last element of the list

% 1.1 deifition using append

last(List, X) :- app(_,[X], List).

app([], X, X).

app([H|T], L2, [H|Acc]) :-
    app(T, L2, Acc).

last2([X], X).
last2([_|T], X) :-
    last2(T, X).

% 2.1 max_age(List, Max).

% Procedural definition

% Base case
max_age_proc(List, Max) :-
    List = [X], % Ensure list has 1 element
    X = (_, _, Age), % Get the Age from the first element
    Max = Age.% Set Max = Age

max_age_proc(List, Max) :-
    List = [H|T], % Get the head of the list
    H = (_, _, Age), % Get the Age from the head
    max_age_proc(T, MaxRest), % Recursive call to get the max from the rest of the list
    (
        Age > MaxRest 
        -> 
        Max = Age 
        ; 
        Max = MaxRest
    ). % Determine whether age is larger than the rest and set Max

% declarative definition

max_age_dec([(_,_,Age)], Age).

% don't forge the y to make the call mutually exclusive '
max_age_dec([(_,_,Age), Y|T], Max) :-
    max_age_dec([Y|T], MaxRest),
    bigger(MaxRest, Age, Max).

bigger(X, Y, Y) :- Y > X.
bigger(X, Y, X) :- Y =< X.

bigger_of(X, Y, Y) :- Y > X, !.
bigger_of(X, _, X).


% 2.2 max_age(List, Max). | Tail recursive def

% Accumulator call | fails if the list is not empty
max_age([H|T], Age) :-
    max_age([H|T], 0, Age).

max_age([], MaxCurr, MaxCurr).

max_age([(_,_,Age)|T], MaxCurr, Max) :-
    bigger_of(Age, MaxCurr, NextMax),
    max_age(T, NextMax, Max).
    
% 2.3 average_age(List, Average).

% Acc caller
average_age([H|T], Average) :-
    age_stats_avg([H|T], 0, 0, N, SumAges),
    Average is SumAges / N.
% fails if the list is empty

% the second and third args are Accs
age_stats_avg([], N, Sum, N, Sum).

age_stats_avg([(_,_,Age)|T], N, Acc, N_final, Sum) :-
    NextAcc is Acc + Age,
    NextN is N + 1,
    age_stats_avg(T, NextN, NextAcc, N_final, Sum).
    
% 2.4 max_avg_age([H|T], Max, Avg) :-
max_avg_age([H|T], Max, Avg) :-
    age_stats([H|T], 0, 0, 0, N, Sum, Max),
    Avg is Sum / N.
    
age_stats([], N, Sum, Max, N, Sum, Max).
    
age_stats([(_,_,Age)|T], NAcc, SumAcc, MaxAcc, N, Sum, Max) :-
    SumNext is SumAcc + Age,
    NNext is NAcc + 1,
    ( Age > MaxAcc -> MaxNext = Age ; MaxNext = MaxAcc),
    age_stats(T, NNext, SumNext, MaxNext, N, Sum, Max).
    
% 3 Find a list of the oldest people, tail recursive

% (Person, Sex, Age)

oldest_people([(Person, _, Age)|T], Oldest) :-
    oldest_people(T, Age, [Person], Oldest).

oldest_people([], _, Oldest, Oldest).
oldest_people([(Person, _, Age)|T], AgeAcc, PersonAcc, Oldest) :-
    (
        Age > AgeAcc -> AgeNext = Age, OldestNext = [Person]
        ;
        Age = AgeAcc -> AgeNext = Age, OldestNext = [Person|PersonAcc]
        ;
        Age < AgeAcc -> AgeNext = AgeAcc, OldestNext = PersonAcc
    ),
    oldest_people(T, AgeNext, OldestNext, Oldest).