% -------- Facts --------

has_feathers(sparrow).
has_feathers(parrot).
has_feathers(penguin).
has_feathers(ostrich).
has_feathers(eagle).

can_fly(sparrow).
can_fly(parrot).
can_fly(eagle).

lays_eggs(sparrow).
lays_eggs(parrot).
lays_eggs(penguin).
lays_eggs(ostrich).
lays_eggs(eagle).

swims(penguin).

strong_beak(parrot).

% -------- Rules --------

bird(X) :-
    has_feathers(X),
    lays_eggs(X).

flying_bird(X) :-
    bird(X),
    can_fly(X).

non_flying_bird(X) :-
    bird(X),
    \+ can_fly(X).

water_bird(X) :-
    bird(X),
    swims(X).

pet_bird(X) :-
    bird(X),
    strong_beak(X).

wild_bird(X) :-
    bird(X),
    can_fly(X),
    \+ strong_beak(X).
    
% -------- Facts --------

has_feathers(sparrow).
has_feathers(parrot).
has_feathers(penguin).
has_feathers(ostrich).
has_feathers(eagle).

can_fly(sparrow).
can_fly(parrot).
can_fly(eagle).

lays_eggs(sparrow).
lays_eggs(parrot).
lays_eggs(penguin).
lays_eggs(ostrich).
lays_eggs(eagle).

swims(penguin).

strong_beak(parrot).

% -------- Rules --------

bird(X) :-
    has_feathers(X),
    lays_eggs(X).

flying_bird(X) :-
    bird(X),
    can_fly(X).

non_flying_bird(X) :-
    bird(X),
    \+ can_fly(X).

water_bird(X) :-
    bird(X),
    swims(X).

pet_bird(X) :-
    bird(X),
    strong_beak(X).

wild_bird(X) :-
    bird(X),
    can_fly(X),
    \+ strong_beak(X).