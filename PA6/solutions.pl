% Problem 1
% Facts Shown Here!
parent(bart,homer).
parent(bart,marge).
parent(lisa,homer).
parent(lisa,marge).
parent(maggie,homer).
parent(maggie,marge).
parent(homer,abraham).
parent(herb,abraham).
parent(tod,ned).
parent(rod,ned).
parent(marge,jackie).
parent(patty,jackie).
parent(selma,jackie).

female(maggie).
female(lisa).
female(marge).
female(patty).
female(selma).
female(jackie).

male(bart). 
male(homer).
male(herb).
male(burns).
male(smithers).
male(tod).
male(rod).
male(ned).
male(abraham).

% Rules Shown Here!
brother(X,Y) :- male(Y), parent(X,A), parent(Y,B), A=B, X\=Y.
sister(X,Y) :- female(Y), parent(X,A), parent(Y,B), A=B, X\=Y.
aunt(X,Y) :- parent(X,A), sister(A,Y). 
uncle(X,Y) :- parent(X,A), brother(A,Y). 
grandfather(X,Y) :- male(Y), parent(X,A), parent(A,Y).
granddaughter(X,Y) :- female(Y), parent(Y,A), parent(A,X).
ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- parent(X,A), ancestor(A,Y).
related(X,Y) :- ancestor(X,Y).
related(X,Y) :- ancestor(X,A), related(Y,A).
unrelated(X,Y) :- \+ related(X,Y).


% Problem 2
% Facts shown here!
occupation(joe,oral_surgeon).
occupation(sam,patent_laywer).
occupation(bill,trial_laywer).
occupation(cindy,investment_banker).
occupation(joan,civil_laywer).
occupation(len,plastic_surgeon).
occupation(lance,heart_surgeon).
occupation(frank,brain_surgeon).
occupation(charlie,plastic_surgeon).
occupation(lisa,oral_surgeon).

address(joe,houston).
address(sam,pittsburgh).
address(bill,dallas).
address(cindy,omaha).
address(joan,chicago).
address(len,college_station).
address(lance,los_angeles).
address(frank,dallas).
address(charlie,houston).
address(lisa,san_antonio).

salary(joe,50000).
salary(sam,150000).
salary(bill,200000).
salary(cindy,140000).
salary(joan,80000).
salary(len,70000).
salary(lance,650000).
salary(frank,85000).
salary(charlie,120000).
salary(lisa,190000).

surgeon(oral_surgeon).
surgeon(plastic_surgeon).
surgeon(heart_surgeon).
surgeon(brain_surgeon).




tx(houston).
tx(dallas).
tx(college_station).
tx(san_antonio).


% Answer
txsurgeon100k(X) :- occupation(X,Y), surgeon(Y), address(X,Z), tx(Z), salary(X,A), A > 100000.

% Problem 3
% Facts shown here!
subject(algebra,math).
subject(calculus,math).
subject(dynamics,physics).
subject(electromagnetism,physics).
subject(nuclear,physics).
subject(organic,chemistry).
subject(inorganic,chemistry).

degree(bill,phd,chemistry).
degree(john,bs,math).
degree(chuck,ms,physics).
degree(susan,phd,math).

retired(bill).

% Answer
canTeach(X,Y) :- subject(Y,Z), degree(X,D,Z), D=='phd'.
canTeach2(X,Y) :- subject(Y,Z), degree(X,D,Z), (D == 'phd' ; D == 'ms').
% assumes that candidate must have ONLY PHD and not masters
canTeach3(X,Y) :- subject(Y,Z), degree(X,D,Z), D=='phd', \+ retired(X). 

% Problem 4
countup1(A,B) :- A<B, countup(A,B).
countup(A,B) :- A == B, format('~w~n',[B]).
countup(A,B) :- B>A, M is B-1, countup(A,M), format('~w~n',[B]).

countup2(A,B) :- A<B, countup2(A,B,B).
countup2(A,B,C) :- A == C, format('~w~n',[B]).
countup2(A,B,C) :- C>A, D is B-C+A, format('~w~n',[D]), M is C-1, countup2(A,B,M).

countup3(A,B) :- A<B, countup3(A,B,A).
countup3(A,B,C) :- B == C, format('~w~n',[B]).
countup3(A,B,C) :- C<B, format('~w~n',[C]), M is C+1, countup3(A,B,M).