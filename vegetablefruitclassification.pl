:- initialization(main, main).

main :-
    write('Fruits:'), nl,
    (fruit(X), write(X), nl, fail ; true),

    write('Vegetables:'), nl,
    (vegetable(X), write(X), nl, fail ; true),

    write('Citrus fruits:'), nl,
    (citrus_fruit(X), write(X), nl, fail ; true),

    write('Leafy vegetables:'), nl,
    (leafy_vegetable(X), write(X), nl, fail ; true),

    write('Root vegetables:'), nl,
    (root_vegetable(X), write(X), nl, fail ; true).