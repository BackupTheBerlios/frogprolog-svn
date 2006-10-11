mann(karl).
mann(alois).
mann(dieter).
mann(herbert).
mann(gunter).
mann(ulrich).
mann(udo).
mann(lutz).
mann(hugo).
mann(fred).
mann(otto).
mann(heinz).
mann(peter).
mann(anton).
mann(bert).
mann(jakob).
mann(manfred).
mann(klaus).
mann(fritz).
mann(jens).
mann(xaver).

frau(lisa).
frau(klara).
frau(anna).
frau(helga).
frau(susanne).
frau(elke).
frau(ulrike).
frau(inge).
frau(luise).
frau(magda).
frau(steffi).
frau(petra).
frau(ruth).
frau(thea).
frau(christa).
frau(helen).
frau(maria).
frau(isolde).
frau(erika).
frau(elsa).
frau(lena).
frau(vera).

elternteil(alois, udo).    
elternteil(alois, heinz).
elternteil(thea, udo).
elternteil(thea, heinz).
elternteil(jakob, bert).
elternteil(jakob, christa).
elternteil(jakob, isolde).
elternteil(elsa, bert).
elternteil(elsa, christa).
elternteil(elsa, isolde).
elternteil(fritz, ulrich).
elternteil(fritz, susanne).
elternteil(fritz, lena).
elternteil(ulrike, ulrich).
elternteil(ulrike, susanne).
elternteil(ulrike, lena).
elternteil(jens, elke).
elternteil(jens, helga).
elternteil(jens, erika).
elternteil(anna, elke).
elternteil(anna, helga).
elternteil(anna, erika).
elternteil(anton, hugo).
elternteil(anton, lutz).
elternteil(anton, steffi).
elternteil(magda, hugo).
elternteil(magda, lutz).
elternteil(magda, steffi).
elternteil(herbert, peter).
elternteil(maria, peter).
elternteil(dieter, luise).
elternteil(ruth, luise).
elternteil(karl, fred).
elternteil(inge, fred).
elternteil(otto, alois).
elternteil(otto, fritz).
elternteil(otto, jens).
elternteil(lisa, alois).
elternteil(lisa, fritz).
elternteil(lisa, jens).
elternteil(manfred, thea).
elternteil(manfred, elsa).
elternteil(helen, thea).
elternteil(helen, elsa).
elternteil(helen, anton).
elternteil(xaver, anna).
elternteil(xaver, magda).
elternteil(vera, anna).
elternteil(vera, magda).
elternteil(gunter, ulrike).
elternteil(klara, ulrike).
elternteil(gunter, jakob).
elternteil(klara, jakob).

verheiratet(alois, thea).
verheiratet(jakob, elsa).
verheiratet(jens, anna).
verheiratet(anton, magda).
verheiratet(dieter, ruth).
verheiratet(otto, lisa).
verheiratet(manfred, helen).
verheiratet(gunter, klara).

geschwister(K1, K2) :- elternteil(X,K1), elternteil(X, K2), K1 \= K2, write(geschwister(K1, K2)), nl.

person(X) :- mann(X).
person(X) :- frau(X).

kein_kind(X) :- 
   person(X), not(elternteil(X,_)), write(kein_kind(X)), nl.


init :- ( 
             geschwister(udo, X),
             fail;
             true
        ),
        ( 
             kein_kind(X),
             fail;
             true
        ).
        
        
        