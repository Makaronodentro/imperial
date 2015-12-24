% Name    : hogwarts.pl
% Author  : Georgios Kontogiannis
% CID     : 00876225
% Due date: 30th of November 2015

% the students in Hogwarts
% student(fk, 'fil', gryffindor). % student with no options for error checking
                                % Uncomment to use
student(gk, 'Georgios Leandros Kontogiannis', gryffindor). % Ex. 1
student(hp, 'Harry James Potter', gryffindor).
student(hg, 'Hermione Jean Granger', gryffindor).
student(rw, 'Ronald Weasley', gryffindor).
student(ll, 'Luna Lovegood', ravenclaw).
student(cc, 'Cho Chang', ravenclaw).
student(tb, 'Terry Boot', ravenclaw).
student(ha, 'Hannah Abbott', hufflepuff).
student(cd, 'Cedric Diggory', hufflepuff).
student(nt, 'Nymphadora Tonks',hufflepuff).
student(dm, 'Draco Malfoy', slytherin).
student(gg, 'Gregory Goyle', slytherin).
student(vc, 'Vincent Crabbe', slytherin).

% the teachers in Hogwarts
teacher(ad, 'Albus Percival Wulfric Brian Dumbledore').
teacher(ff, 'Filius Flitwick').
teacher(rh, 'Rubeus Hagrid').
teacher(gl, 'Gilderoy Lockhart').
teacher(rl, 'Remus John Lupin').
teacher(mm, 'Minerva McGonagall').
teacher(qq, 'Quirinus Quirrell').
teacher(ss, 'Severus Snape').
teacher(ps, 'Pomona Sprout').
teacher(st, 'Sibyll Patricia Trelawney').
teacher(mh, 'Madam Hooch').
teacher(as, 'Aurora Sinistra').
teacher(cub, 'Cuthbert Binns').
teacher(bb, 'Bathsheba Babbling').
teacher(sv, 'Septima Vector').
teacher(chb, 'Charity Burbage').
teacher(wt, 'Wilkie Twycross').

% compulsory courses for the MSc in Magic
compCourse(astro, 'Astronomy', as).
compCourse(charms, 'Charms', ff).
compCourse(defence, 'Defence against the Dark Arts', qq).
compCourse(fly, 'Flying', mh).
compCourse(herb, 'Herbology', ps).
compCourse(history, 'History of Magic', cub).
compCourse(potions, 'Potions', ss).
compCourse(trans, 'Transfiguration', mm).

% optional courses for the MSc in Magic
optCourse(runes, 'Study of Ancient Runes', bb).
optCourse(arith, 'Arithmancy', sv).
optCourse(muggle, 'Muggle Studies', chb).
optCourse(creatures, 'Care of Magical Creatures', rh).
optCourse(div, 'Divination', st).
optCourse(app, 'Apparition', wt).
optCourse(choir, 'Frog Choir', ff).
optCourse(quid, 'Quidditch', mh).

% Ex. 2
% student options  enrolled_opt(SID, SCN).
enrolled_opt(gk, arith).
enrolled_opt(gk, creatures).
enrolled_opt(gk, runes).
enrolled_opt(hp, quid).
enrolled_opt(hp, div).
enrolled_opt(hp, creatures).
enrolled_opt(hg, runes).
enrolled_opt(hg, arith).
enrolled_opt(hg, div).
enrolled_opt(hg, creatures).
enrolled_opt(hg, app).
enrolled_opt(hg, quid).
enrolled_opt(rw, quid).
enrolled_opt(rw, creatures).
enrolled_opt(rw, div).
enrolled_opt(ll, runes).
enrolled_opt(ll, div).
enrolled_opt(ll, choir).
enrolled_opt(cc, arith).
enrolled_opt(cc, quid).
enrolled_opt(cc, creatures).
enrolled_opt(tb, arith).
enrolled_opt(tb, muggle).
enrolled_opt(tb, app).
enrolled_opt(ha, app).
enrolled_opt(ha, arith).
enrolled_opt(ha, runes).
enrolled_opt(cd, muggle).
enrolled_opt(cd, creatures).
enrolled_opt(cd, choir).
enrolled_opt(nt, arith).
enrolled_opt(nt, app).
enrolled_opt(nt, div).
enrolled_opt(dm, arith).
enrolled_opt(dm, runes).
enrolled_opt(dm, div).
enrolled_opt(gg, choir).
enrolled_opt(gg, quid).
enrolled_opt(gg, creatures).
enrolled_opt(vc, choir).
enrolled_opt(vc, quid).
enrolled_opt(vc, creatures).

% Ex. 3
% enrolled(?SID, ?SCN).
% ------------------------------------------------------------------------------
% The student whose ID is SID is enrolled on the course with short name SCN 
% (this can be a compulsory or an optional course).

enrolled(SID, SCN) :-
    % validate student ID
    student(SID,_,_),
    % Get short course name in which student is enrolled
    (compCourse(SCN, _, _) ; enrolled_opt(SID, SCN)).
    
   
% Ex. 4
% teaches(?TN, ?SCN)
% ------------------------------------------------------------------------------ 
% The wizard/witch whose name is TN (not the ID!) teaches the magical course 
% with short name SCN.

teaches(TN, SCN) :-
    % Get teacher ID
    teacher(TID, TN), 
    % Get short course name the teacher teaches
    (compCourse(SCN, _, TID) ; optCourse(SCN, _, TID)).
    
    
    
% Ex. 5
% taughtBy(?SN, ?TN)
% ------------------------------------------------------------------------------ 
% The student SN is enrolled on a magical course that is taught by TN, where TN 
% is the teacher’s name and SN the student’s name.
% In the case that a student name x is taught by a teacher y on two courses and
% you query “taughtBy(SN,TN)”, it is completely normal that you get 
% “SN = x, TN = y” twice as a solution.

taughtBy(SN, TN) :-
    student(SID,SN,_), % Get Student ID
    enrolled(SID, SCN), % Get student's courses
    teaches(TN, SCN). % See if the teacher teaches it 
    
% Ex. 6 
% takesOption(?SN, ?CN)
% ------------------------------------------------------------------------------
% The student SN is enrolled on the optional course called CN.

takesOption(SN, CN) :-
    student(SID, SN, _), % Get student ID
    optCourse(SCN, CN, _), % Get optCourse short name
    enrolled_opt(SID, SCN). % confim that student is enrolled in the course
    
% Ex. 7 
% takesAllOptions(?SN, ?OptCourses)
% ------------------------------------------------------------------------------
% OptCourses is the list of all optional magical courses the student called 
% SN chose. The list OptCourses contains the names of these magical courses 
% in alphabetical order.
% If you query an invalid student name, Prolog's answer should be “no”. 
% You can assume that every valid student takes optional courses 
% (so OptCourses will never be the empty list).

% Last line implies that in case of no enrolled options return false

takesAllOptions(SN, L) :-
    student(_, SN, _), % confirm student, returns false for invalid.
    setof(CN,takesOption(SN, CN), L). % Get sorted list of optCourses
    
% Ex. 8
% studentsInHouse(?House, ?Students)
% ------------------------------------------------------------------------------
% Students is the list of all student names (!) which are part of a particular
% House. The list is ordered alphabetically by the respective students’ ID (!). 
% This means that you have to order the list Students by ID, even though it 
% contains only the respective names.
% House is one of gryffindor, hufflepuff, ravenclaw, or slytherin. For an 
% invalid House, Prolog's answer should be “no”. If a valid House does not 
% have any students, then Students should be the empty list.

% define houses for individual checking
house(gryffindor).
house(hufflepuff).
house(ravenclaw).
house(slytherin).
%house(empty). % Define an empty house for error checking, uncomment to use

studentsInHouse(HS, SNs) :-
    house(HS), % check for valid house
    (student(_,_,HS) -> % If the house has at least 1 student
    % get the ordered list of students
    setof(SN,[HS,SID]^student(SID, SN, HS), SNs) ; 
    SNs = []). % else return an empty list
    
% Ex. 9
% studentsOnCourse(?SCN, ?CN, ?StudentsByHouse)
% ------------------------------------------------------------------------------
% For a magical course CN with short course name SCN (this can be a compulsary 
% or an optional course), the list StudentsByHouse has 4 elements of the form 
% House-Students, one for each house. House is one of gryffindor, hufflepuff, 
% ravenclaw, or slytherin, and Students is a list consisting of all students
% (their names) in the respective House enrolled on the course CN/SCN:
% 
% studentsOnCourse(SCN, CN, [gryffindor-GryffindorList, 
% hufflepuff-HufflepuffList, ravenclaw-RavenclawList, slytherin-SlytherinList])
% The order of student names in the list Students does not matter. If no student
% of a certain house takes the course, then the respective list of Students is 
% the empty list. This means, that if no students at all are taking a course 
% with name cn and short name scn and you query StudentsOnCourse(scn, cn, 
% StudentsByHouse), the solution should be 2StudentsByHouse = [gryffindor-[], 
% hufflepuff-[], ravenclaw-[], slytherin-[]]. 
% However, if you are querying a non-existing course, the answer should be “no”.

% Returns a list of all students in a house, taking a specific course
studentsOnCourseInHouse(HS, SCN, SNs) :-
   % Specify house
   house(HS), 
   % Get all students in the house studying SCN
   findall(SN, (student(SID, SN, HS),enrolled(SID, SCN)), SNs).


studentsOnCourse(SCN, CN, SHB) :-
    % check for valid course
    (compCourse(SCN, CN, _) ; optCourse(SCN, CN, _)),
    % Get all students studying the course
    findall(HS-SNs, studentsOnCourseInHouse(HS, SCN, SNs), SHB).
    

% Ex. 10
% sharedCourse(?SN1, ?SN2, ?CN)
% ------------------------------------------------------------------------------
% The optional magical course with name CN is taken by two different students 
% with names SN1 and SN2.
% It is normal that your sharedCourse succeeds for/generates both 
% sharedCourse(name1, name2, cn) and sharedCourse(name2, name1, cn) for any 
% two people name1 and name2 who share the course named cn.

sharedCourse(SN1, SN2, CN) :-
    % Get and optional course for the student
    takesOption(SN1, CN),
    % Find another student taking the same course
    takesOption(SN2, CN),
    % Ensure its not the same student
    SN1 \= SN2.

% Ex. 11
% sameOptions(?SN1, ?SN2, ?Courses)
% ------------------------------------------------------------------------------
% Two differerent students SN1 and SN2 are enrolled on exactly the same three 
% optional courses, which form the list Courses of course names (the order does 
% not matter). Since Hermione is taking 6 instead of 3 optional courses, we 
% will say that she has the same courses as another student if 3 out of her 6 
% magical courses match the other student’s courses.
% Again, it is normal that your predicate succeeds for/generates both
% sameOptions(name1, name2, courselist) & sameOptions(name2, name1, courselist).

sameOptions(SN1, SN2, Cs) :-
    % Get all options for a student
    takesAllOptions(SN1, Cs_1), % Note takesAllOptions returns a sorted list 
    % Get options for a second student
    takesAllOptions(SN2, Cs_2), 
    SN1\=SN2, % ensure students 1 and 2 are not the same
    (sublist(Cs_1, Cs_2) -> Cs = Cs_1 ; % If Course List 1 is sublist of Cs_2
                                        % set Common Course List equal to Cs_1
     sublist(Cs_2, Cs_1) -> Cs = Cs_2). % If Course List 2 is sublist of Cs_1
                                        % set Common Course List equal to Cs_2
    
% sublist(?Sublist, +List). Elements must be sorted
sublist([], _). % base case, an empty list is sublist of anything 
sublist([H|T1], [H|T2]) :- 
    sublist(T1, T2). % check for identical headers
sublist([H|T1], [_|T2]) :- 
    sublist([H|T1], T2). % if header not the same, cut head of list 2
    % if list 2 becomes empty and list 1 is not, return false.