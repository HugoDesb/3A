heads = constantes_type_graphe.h fonctions_graphe.h

run :
	$(MAKE) all
	./monprog > ma_reponse
	diff ma_reponse la_reponse_de_reference | more

all : monprog

monprog : libgra.a main.o
	gcc -o monprog -O3 -Wall -L. -lgra fonctions_graphe.o main.o

main.o : $(heads) main.c ma_contribution.c
	gcc -c -O3 -Wall main.c

libgra.a : $(heads) fonctions_graphe.c
	gcc -c -O3 -Wall -Werror fonctions_graphe.c
	ar -r libgra.a fonctions_graphe.o

clean :
	rm -f *.o

veryclean : clean
	rm -f monprog libgra.a ma_reponse
