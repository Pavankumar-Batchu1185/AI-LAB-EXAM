:- initialization(main, main).

main :-
    write('=== Sentiment Analysis System ==='), nl,
    write('Enter a word (with dot at end, e.g. good.): '),
    read(Word),
    analyze(Word).

% -------- Analysis Logic --------

analyze(Word) :-
    sentiment(Word, positive), !,
    write('Word: '), write(Word), nl,
    write('Sentiment: POSITIVE'), nl.

analyze(Word) :-
    sentiment(Word, negative), !,
    write('Word: '), write(Word), nl,
    write('Sentiment: NEGATIVE'), nl.

analyze(Word) :-
    sentiment(Word, neutral), !,
    write('Word: '), write(Word), nl,
    write('Sentiment: NEUTRAL'), nl.

analyze(Word) :-
    write('Word: '), write(Word), nl,
    write('Sentiment: Word not found in database.'), nl.

% -------- Facts --------

positive(good).
positive(happy).
positive(excellent).
positive(love).
positive(great).
positive(amazing).

negative(bad).
negative(sad).
negative(terrible).
negative(hate).
negative(worst).
negative(angry).

neutral(okay).
neutral(fine).
neutral(average).

% -------- Rules --------

is_positive(X) :- positive(X).
is_negative(X) :- negative(X).
is_neutral(X)  :- neutral(X).

sentiment(X, positive) :- positive(X).
sentiment(X, negative) :- negative(X).
sentiment(X, neutral)  :- neutral(X).