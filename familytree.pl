:- initialization(main, main).

main :-
    write('Grandfathers of mike:'), nl,
    (grandfather(X, mike), write(X), nl, fail ; true),

    write('Grandmothers of mike:'), nl,
    (grandmother(X, mike), write(X), nl, fail ; true),

    write('Father of mike:'), nl,
    (father(X, mike), write(X), nl, fail ; true),

    write('Mother of mike:'), nl,
    (mother(X, mike), write(X), nl, fail ; true),

    write('Siblings of paul:'), nl,
    (sibling(X, paul), write(X), nl, fail ; true),

    write('Brothers of paul:'), nl,
    (brother(X, paul), write(X), nl, fail ; true),

    write('Sisters of paul:'), nl,
    (sister(X, paul), write(X), nl, fail ; true),

    write('Uncles of mike:'), nl,
    (uncle(X, mike), write(X), nl, fail ; true),

    write('Aunts of mike:'), nl,
    (aunt(X, mike), write(X), nl, fail ; true),

    write('Sons of john:'), nl,
    (son(X, john), write(X), nl, fail ; true),

    write('Daughters of john:'), nl,
    (daughter(X, john), write(X), nl, fail ; true).

% --------- Facts ------

male(john).
male(paul).
male(mike).

female(mary).
female(lisa).
female(anna).

parent(john, paul).
parent(mary, paul).

parent(john, lisa).
parent(mary, lisa).

parent(paul, mike).
parent(anna, mike).

% --------- Rules ------

%Father
  father(X,Y) :-
       male(X),
       parent(X,Y).

%Mother
  mother(X,Y) :-
      female(X),
      parent(X,Y).

%Sibling
  sibling(X,Y) :-
      parent(Z,X),
      parent(Z,Y),
      X\=Y.

%Brother
   brother(X,Y) :-
      male(X),
      sibling(X,Y).

%Sister
   sister(X,Y) :-
       female(X),
       sibling(X,Y).

%Grandparent
   grandparent(X,Y) :-
       parent(X,Z),
       parent(Z,Y).

%Grandmother
   grandmother(X,Y) :-
       female(X),
       grandparent(X,Y).
%Granfather
   grandfather(X,Y) :-
       male(X),
       grandparent(X,Y).
%Uncle
   uncle(X,Y) :-
      brother(X,Z),
      parent(Z,Y).

%Aunt
   aunt(X,Y) :-
      sister(X,Z),
      parent(Z,Y).

%Son
   son(X,Y) :-
      male(X),
      parent(Y,X).

%Daughter
   daughter(X,Y) :-
      female(X),
      parent(Y,X).

