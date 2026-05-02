:- initialization(main, main).

:- dynamic yes/1, no/1.

main :-
    write('=== Job Recommendation Expert System ==='), nl,
    write('Answer the following questions (yes/no with dot at end):'), nl, nl,
    ask(python),
    ask(sql),
    ask(machine_learning),
    ask(html),
    ask(css),
    ask(javascript),
    ask(java),
    nl,
    check_recommendations.

% -------- Ask Skills --------

ask(Skill) :-
    write('Do you know '), write(Skill), write('? '),
    read(Response),
    (   Response == yes
    ->  assert(yes(Skill))
    ;   assert(no(Skill))
    ).

% -------- Recommendation Logic --------

check_recommendations :-
    findall(Job, job_match(Job), Jobs),
    (   Jobs == []
    ->  write('No matching job found based on your skills.'), nl
    ;   write('Recommended Jobs:'), nl,
        print_jobs(Jobs)
    ),
    clear.

print_jobs([]).
print_jobs([Job|Rest]) :-
    write('- '), write(Job), nl,
    print_jobs(Rest).

has_skill(Skill) :-
    yes(Skill).

clear :-
    retract(yes(_)), fail.
clear :-
    retract(no(_)), fail.
clear.

% -------- Facts --------

requires(data_scientist, python).
requires(data_scientist, sql).
requires(data_scientist, machine_learning).

requires(web_developer, html).
requires(web_developer, css).
requires(web_developer, javascript).

requires(software_engineer, java).
requires(software_engineer, sql).

% -------- Rules --------

job_match(Job) :-
    requires(Job, _),
    \+ (requires(Job, Skill),
        \+ has_skill(Skill)).

recommend(Job) :-
    job_match(Job).