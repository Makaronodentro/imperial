% Name    : natLang.pl
% Author  : Georgios Kontogiannis
% CID     : 00876225
% Due date: 15th of December 2015

sentence(S)  :- noun_phrase(NP), verb_phrase(VP), append(NP, VP, S).

noun_phrase(NP):- article(A), noun(N), append(A, N, NP). 

verb_phrase(V):- verb(V).
verb_phrase(VP):- verb(V), noun_phrase(NP), append(V, NP, VP).

% The Lexicon:

article([the]).
article([a]).
article([an]).

noun([grass]).
noun([cow]).
noun([girl]).
noun([boy]).
noun([apple]).
noun([song]).

verb([eats]).
verb([sings]).
verb([chews]).
verb([kicks]).

% Ex. 3b
adverb([slowly]). 
adverb([deliberately]). 
adverb([merrily]). 
adverb([sweetly]).

% Ex. 1a
conj([and]).

% Ex. 1a
% count_sentences(?Text, ?Count)
% ------------------------------------------------------------------------------
% a) Write a program for count_sentences(Text, Count), where Text is a 
% conjunction of sentences, and Count is the number of sentences in Text. 
% In all calls you can assume that Text is ground.

% Base case for empty list
count_sentences([], 0).

% Base case for the last simple sentence.
count_sentences(S, 1) :- sentence(S).

% Recursive calls
count_sentences(S, Count) :-
    sentence(H), % Check if the front is a sentence
    conj([C]), % Check if the head of the rest of the list is an "and"
    append(H,[C|T],S), % break the list in three parts
    count_sentences(T, PrevCount), % count sentences in the tail
    Count is PrevCount + 1. % Once add 1 to the result of the recursive call

% NOTE: In case of incorrect grammar return false (conjucntion of SENTENCES)
%       count_sentences(S, X). Returns infnite conjunctions of sentences


% Ex. 1b
% actions(?Actor, +Text, ?As)
% ------------------------------------------------------------------------------
% b) Write a program for actions(Actor, Text, As) such that As is the list of 
% actions that the Actor does according to the Text. You do not need to check 
% that Text is a conjunction of sentences. You can assume that it is in all 
% calls to actions.
	
 % Ensures that the actor is in the text
 % Placed in a predicate, so that it can be called again despite the cut
inText(Actor, Text) :- 
	member(Actor, Text),!. % Cut needed to avoid duplicate answers

actions(Actor, Text, As) :-
	noun([Actor]), % check if the actor is a noun
	inText(Actor, Text), % get only the Actors inside the text
	/* Get all the instances of an Act in the Text where it follows Actor
	 * and place them in the list As */
	findall(Act, 
				(
					append(_,[Actor,Act|_],Text), % Rule1: Act preceded by Actor
					verb([Act]) % Rule2: Act is a verb
				),
			As).
% NOTE: Returns empty list for Actors in the text that don't act.
%       Returns false for Actors that are not in the text.

% Ex. 2
% noun_phrase_better(?Phrase)
% ------------------------------------------------------------------------------
% Modify the program in the starter file natLang.pl for noun_phrase/1 to a 
% program noun_phrase_better/1 so that it requires the article to match the
% noun in noun phrases, i.e. if the noun starts with a vowel then the article
% is either ‘the’ or ‘an’, not ‘a’, and if the noun starts with a consonant
% then the article is either ‘the’ or ‘a’, not ‘an’. 

% Returns true if the first char of the word is a vowel.
checkVowel([Word]) :-
	atom_chars(Word, [Letter|_]), % Letter is set to first char of word
	member(Letter, [a, e, i, o, u]). % Letter can be a vowel


noun_phrase_better(Phrase) :-
	article(A), % Get an article
	noun(N), % Get a noun
	(checkVowel(N) -> % check if the noun starts with a vowel
	member(A, [[the], [an]]); % if it does, options for A are the, an
	member(A, [[the], [a]])), % if it doesn't, options for A are the, a
	append(A, N, Phrase). % Try to append A and N to phrase


% Ex. 3a
% cadvs(?L)
% ------------------------------------------------------------------------------
% Define a predicate cadvs/1 such that cadvs(L) means L is conjunction of 
% adverbs according to the specification below.
% Extend the grammar so that your program can also deal with verb phrases that 
% consist of a conjunction of adverbs, followed by a verb, followed by a noun 
% phrase. An example of a sentence conforming to this extended grammar is 
% “a cow slowly and deliberately chews the grass”. When there are more than 
% two adverbs, all but the final two are separated by commas, and only the final
% two are separated by the word “and”. So, for example
% [slowly, ‘,’, deliberately, and, merrily] is recognized as a conjunction of 
% adverbs, but not [slowly, and, deliberately, and, merrily].
% Also make sure that your program does not allow repetitions of adverbs in the 
% same phrase. So, for example, a sequence of words such as [a, cow, slowly, 
% and, slowly, chews, the, grass] is not accepted or generated as a sentence.

% predicate caller
cadvs(L) :- accCadvs([], L).

% accCads(+Acc, +L). Accumulates L in Acc subject to conditions

% First call
accCadvs([],L) :- % if the Acc is empty (first call)
	adverb(Adv), % get an adverb
	accCadvs(Adv, L). % pass it into the accumulator

% Second call
accCadvs(Acc,L) :-
	length(Acc, 1), % if there is already an adverb in Acc (and can't be last)
	\+member(and, Acc), % if there is no 'and' in the Acc yet
	adverb([Adv]), % get a second adverb
	\+member(Adv,Acc), % make sure that adverb is not part of the Acc yet
	append([Adv],[and],Temp), % append 'and' to the new Adverb
	append(Temp, Acc, NewAcc),  % append temp to the accumulator
	accCadvs(NewAcc, L).

% Subsequent calls
accCadvs(Acc,L) :-	
	member(and, Acc), % if there is an 'and' in the accumulator
	adverb([Adv]), % get an extra adverb
	\+member(Adv,Acc), % make sure that adverb is not part of the Acc yet
	append([Adv],[','],Temp), % append ',' to the new Adverb
	append(Temp, Acc, NewAcc), % append temp to the accumulator
	accCadvs(NewAcc, L).

% Once lists are the same and not empty return
accCadvs(L, L) :- L\=[]. % Also makes sure L returns false for empty lis

% Ex. 3c
% verb_phrase_better(?Phrase)
% ------------------------------------------------------------------------------
% c) Define a predicate verb_phrase_better/1 such that verb_phrase_better(V) 
% means V is a verb phrase, where a verb phrase is now:
% a verb, or
% a verb followed by a better noun phrase, or
% a conjunctions of adverbs followed by a verb, or
% a conjunctions of adverbs followed by a verb, followed by a better 
% noun phrase, according to the specification in (Q2), above.

% a verb
verb_phrase_better(Phrase) :- verb(Phrase).
% a verb followed by a better noun phrase,
verb_phrase_better(Phrase) :- 
	verb(V), 
	noun_phrase_better(NPB), 
	append(V, NPB, Phrase).
% a conjunction of adverbs followed by a verb
verb_phrase_better(Phrase) :- 
	cadvs(Advs), 
	verb(V), 
	append(Advs, V, Phrase).
% a conjunction of adverbs followed by a verb, followed by a better noun phrase
verb_phrase_better(Phrase) :- 
	cadvs(Advs), 
	verb(V), 
	append(Advs, V, PartPhrase),
	noun_phrase_better(NPB),
	append(PartPhrase, NPB, Phrase).

% Ex. 3d
% sentence_better(?Phrase)
% ------------------------------------------------------------------------------
% Define a predicate sentence_better/1 where a better sentence is a better 
% noun phrase (Q2) followed by a better verb phrase (Q3c).

sentence_better(SB) :- 
	noun_phrase_better(NPB),
	verb_phrase_better(VPB),
	append(NPB, VPB, SB).