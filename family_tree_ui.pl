:- initialization(main, main).

main :-
    write('=== Family Tree Expert System ==='), nl,
    write('Known people: john, paul, mike, david, kevin, lisa, susan, anna, kate, emma'), nl, nl,
    write('Enter first person (with dot at end, e.g. john.): '),
    read(X),
    write('Enter second person (with dot at end): '),
    read(Y),
    write('Enter relation (father/mother/sibling/brother/sister/grandfather/grandmother/uncle/aunt/cousin/ancestor): '),
    nl,
    read(Relation),
    check_relation(Relation, X, Y).

% -------- Relation Checking --------

check_relation(father, X, Y) :-
    father(X, Y), !,
    write('TRUE: '), write(X), write(' is the father of '), write(Y), nl.

check_relation(mother, X, Y) :-
    mother(X, Y), !,
    write('TRUE: '), write(X), write(' is the mother of '), write(Y), nl.

check_relation(sibling, X, Y) :-
    sibling(X, Y), !,
    write('TRUE: '), write(X), write(' and '), write(Y), write(' are siblings.'), nl.

check_relation(brother, X, Y) :-
    brother(X, Y), !,
    write('TRUE: '), write(X), write(' is the brother of '), write(Y), nl.

check_relation(sister, X, Y) :-
    sister(X, Y), !,
    write('TRUE: '), write(X), write(' is the sister of '), write(Y), nl.

check_relation(grandfather, X, Y) :-
    grandfather(X, Y), !,
    write('TRUE: '), write(X), write(' is the grandfather of '), write(Y), nl.

check_relation(grandmother, X, Y) :-
    grandmother(X, Y), !,
    write('TRUE: '), write(X), write(' is the grandmother of '), write(Y), nl.

check_relation(uncle, X, Y) :-
    uncle(X, Y), !,
    write('TRUE: '), write(X), write(' is the uncle of '), write(Y), nl.

check_relation(aunt, X, Y) :-
    aunt(X, Y), !,
    write('TRUE: '), write(X), write(' is the aunt of '), write(Y), nl.

check_relation(cousin, X, Y) :-
    cousin(X, Y), !,
    write('TRUE: '), write(X), write(' and '), write(Y), write(' are cousins.'), nl.

check_relation(ancestor, X, Y) :-
    ancestor(X, Y), !,
    write('TRUE: '), write(X), write(' is an ancestor of '), write(Y), nl.

check_relation(_, _, _) :-
    write('FALSE: Relation not found or does not hold.'), nl.

% -------- Facts --------

male(john).
male(paul).
male(mike).
male(david).
male(kevin).

female(lisa).
female(susan).
female(anna).
female(kate).
female(emma).

parent(john, paul).
parent(john, anna).
parent(lisa, paul).
parent(lisa, anna).

parent(paul, mike).
parent(paul, kate).
parent(susan, mike).
parent(susan, kate).

parent(anna, david).
parent(anna, emma).

parent(mike, kevin).

% -------- Rules --------

father(X, Y) :-
    male(X),
    parent(X, Y).

mother(X, Y) :-
    female(X),
    parent(X, Y).

sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.

brother(X, Y) :-
    male(X),
    sibling(X, Y).

sister(X, Y) :-
    female(X),
    sibling(X, Y).

grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

grandfather(X, Y) :-
    male(X),
    grandparent(X, Y).

grandmother(X, Y) :-
    female(X),
    grandparent(X, Y).

uncle(X, Y) :-
    brother(X, Z),
    parent(Z, Y).

aunt(X, Y) :-
    sister(X, Z),
    parent(Z, Y).

cousin(X, Y) :-
    parent(A, X),
    parent(B, Y),
    sibling(A, B),
    X \= Y.

ancestor(X, Y) :-
    parent(X, Y).

ancestor(X, Y) :-
    parent(X, Z),
    ancestor(Z, Y).