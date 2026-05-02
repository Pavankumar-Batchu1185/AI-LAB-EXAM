:- initialization(main, main).

main :-
    write('=== Animal Expert System ==='), nl,
    write('Known animals: lion, tiger, elephant, giraffe, zebra'), nl, nl,
    write('Enter animal name (with dot at end, e.g. lion.): '),
    read(Animal),
    check_animal(Animal).

check_animal(Animal) :-
    identify(Animal), !,
    write('Animal identified successfully: '),
    write(Animal), nl,
    nl,
    write('Properties:'), nl,
    (has_hair(Animal)      -> write('- has hair')      , nl ; true),
    (eats_meat(Animal)     -> write('- eats meat')     , nl ; true),
    (eats_grass(Animal)    -> write('- eats grass')    , nl ; true),
    (has_mane(Animal)      -> write('- has mane')      , nl ; true),
    (has_stripes(Animal)   -> write('- has stripes')   , nl ; true),
    (has_trunk(Animal)     -> write('- has trunk')     , nl ; true),
    (has_long_neck(Animal) -> write('- has long neck') , nl ; true).

check_animal(_) :-
    write('Animal not found or does not match rules.'), nl.

% -------- Facts --------

has_hair(lion).
has_hair(tiger).
has_hair(elephant).
has_hair(giraffe).
has_hair(zebra).

eats_meat(lion).
eats_meat(tiger).

eats_grass(elephant).
eats_grass(giraffe).
eats_grass(zebra).

has_mane(lion).
has_stripes(tiger).
has_stripes(zebra).
has_trunk(elephant).
has_long_neck(giraffe).

% -------- Rules --------

identify(lion) :-
    has_hair(lion),
    eats_meat(lion),
    has_mane(lion).

identify(tiger) :-
    has_hair(tiger),
    eats_meat(tiger),
    has_stripes(tiger).

identify(elephant) :-
    has_hair(elephant),
    eats_grass(elephant),
    has_trunk(elephant).

identify(giraffe) :-
    has_hair(giraffe),
    eats_grass(giraffe),
    has_long_neck(giraffe).

identify(zebra) :-
    has_hair(zebra),
    eats_grass(zebra),
    has_stripes(zebra).