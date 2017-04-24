parcours([]).
parcours([X|Y]):- write(X), nl, parcours(Y).


meme_longueur([],[]).
meme_longueur([_|L1],[_|L2]) :- meme_longueur(L1,L2).

rang_pair([],[]).
rang_pair([X,Y|L],[Y|U]) :- rang_pair(L,U).



renverser([X|Y],L,R) :- renverser(Y,[X|L],R).
renverser([],L,L).
