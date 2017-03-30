horsdoeuvre(celeri).
horsdoeuvre(pate).
horsdoeuvre(melon).

viande(roti).
viande(steak).

poisson(sole).
poisson(rouget).

dessert(flan).
dessert(fruit).

plat(X) :- viande(X).
plat(X) :- poisson(X).

repas(X,Y,Z) :- horsdoeuvre(X),plat(Y),dessert(Z).
repas(X,Y,Z) :- horsdoeuvre(X),plat(Z),dessert(Y).
repas(X,Y,Z) :- horsdoeuvre(Y),plat(X),dessert(Z).
repas(X,Y,Z) :- horsdoeuvre(Y),plat(Z),dessert(X).
repas(X,Y,Z) :- horsdoeuvre(Z),plat(X),dessert(Y).
repas(X,Y,Z) :- horsdoeuvre(Z),plat(Y),dessert(X).

