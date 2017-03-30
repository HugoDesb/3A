homme(leon).
homme(pierre).
homme(jean).
homme(jacques).
homme(paul).
homme(alain).
homme(luc).

femme(claire).
femme(andree).
femme(lucie).
femme(martine).

pere(paul,luc).
pere(jean,paul).
pere(jean,alain).
pere(leon,lucie).
pere(pierre,jean).
pere(pierre,jacques).
mere(martine,luc).
mere(lucie,paul).
mere(lucie,alain).
mere(claire,lucie).
mere(andree,jean).
mere(andree,jacques).

enfant(X,Y) :- pere(Y,X).
enfant(X,Y) :- mere(Y,X).
fils(X,Y) :- homme(X),enfant(X,Y).
fille(X,Y) :- femme(X),enfant(X,Y).
frere-ou-soeur(X,Y) :- enfant(X,Z),enfant(Y,Z),X\=Y.
frere(X,Y) :- frere-ou-soeur(X,Y),homme(X).
soeur(X,Y) :- frere-ou-soeur(X,Y),femme(X).
grandparent(X,Y) :- enfant(Z,X),enfant(Y,Z).
grandpere(X,Y) :- grandparent(X,Y),homme(X).
grandmere(X,Y) :- grandparent(X,Y),femme(X).


