:- initialization(main, main).

main :-
    write('Vehicles:'), nl,
    (vehicle(X), write(X), nl, fail ; true),

    write('Light vehicles:'), nl,
    (light_vehicle(X), write(X), nl, fail ; true),

    write('Heavy vehicles:'), nl,
    (heavy_vehicle(X), write(X), nl, fail ; true),

    write('Two wheelers:'), nl,
    (two_wheeler(X), write(X), nl, fail ; true),

    write('Four wheelers:'), nl,
    (four_wheeler(X), write(X), nl, fail ; true),

    write('Passenger vehicles:'), nl,
    (passenger_vehicle(X), write(X), nl, fail ; true),

    write('Goods vehicles:'), nl,
    (goods_vehicle(X), write(X), nl, fail ; true).
    
% -------- Facts --------

wheels(car,4).
wheels(bus,4).
wheels(truck,6).
wheels(bike,2).
wheels(scooter,2).

engine(car).
engine(bus).
engine(truck).
engine(bike).
engine(scooter).

heavy(bus).
heavy(truck).

passenger(car).
passenger(bus).

goods(truck).

% -------- Rules --------

vehicle(X) :-
    wheels(X,_),
    engine(X).

light_vehicle(X) :-
    vehicle(X),
    \+ heavy(X).

heavy_vehicle(X) :-
    vehicle(X),
    heavy(X).

two_wheeler(X) :-
    wheels(X,2).

four_wheeler(X) :-
    wheels(X,4).

passenger_vehicle(X) :-
    vehicle(X),
    passenger(X).

goods_vehicle(X) :-
    vehicle(X),
    goods(X).