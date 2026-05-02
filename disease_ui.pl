:- initialization(main, main).

main :-
    write('--- Disease Identification System ---'), nl, nl,
    write('Checking all known diseases:'), nl,
    write('diseases: flu, covid19, malaria, food_poisoning, asthma'), nl, nl,
    write('Enter disease to diagnose (with dot at end, e.g. flu.): '),
    read(Disease),
    check_disease(Disease).

check_disease(Disease) :-
    disease(Disease), !,
    write('--- Diagnosing: '), write(Disease), write(' ---'), nl,
    diagnose(Disease).

check_disease(_) :-
    write('Unknown disease. Not found in knowledge base.'), nl.

diagnose(Disease) :-
    findall(S, symptom(Disease, S), Symptoms),
    check_symptoms(Disease, Symptoms, 0, Score),
    Total=Symptoms,
    length(Total, TotalCount),
    nl,
    write('Symptoms matched: '), write(Score), write('/'), write(TotalCount), nl,
    (   Score=:=TotalCount
    ->  write('Diagnosis: High likelihood of '), write(Disease), nl
    ;   Score > 0
    ->  write('Diagnosis: Possible '), write(Disease), write(' (partial match)'), nl
    ;   write('Diagnosis: Unlikely to be '), write(Disease), nl
    ).

check_symptoms(_, [], Score, Score).
check_symptoms(Disease, [S|Rest], Acc, Score) :-
    write('Does patient have '), write(S), write('? (yes/no): '),
    read(Ans),
    (   Ans=yes
    ->  Acc1 is Acc+1
    ;   Acc1 is Acc
    ),
    check_symptoms(Disease, Rest, Acc1, Score).

% -------- Facts --------

symptom(flu, fever).
symptom(flu, cough).
symptom(flu, headache).

symptom(covid19, fever).
symptom(covid19, cough).
symptom(covid19, loss_of_smell).
symptom(covid19, fatigue).

symptom(malaria, fever).
symptom(malaria, chills).
symptom(malaria, sweating).

symptom(food_poisoning, vomiting).
symptom(food_poisoning, diarrhea).
symptom(food_poisoning, stomach_pain).

symptom(asthma, breathlessness).
symptom(asthma, wheezing).
symptom(asthma, cough).

% -------- Rules --------

disease(X) :-
    symptom(X, _), !.

has_symptom(Disease, Symptom) :-
    symptom(Disease, Symptom).