#---------------------------------------------------------------
# Nom du fichier : makefile
# Auteur :
# Objet : Commandes de compilation du programme de gestion de arbres
#         doublement chainees d'entiers 
# Pour generer l'executable (abr) : tapez "make" ou "make abr"
# Pour effacer les fichiers objet et l'executable : tapez "make clean"
#--------------------------------------------------------------------

abr: main.o arbres.o memoire.o interface.o makefile
	gcc -g -Wall -o abr main.o arbres.o memoire.o interface.o

main.o: main.c arbres.h interface.h makefile
	gcc -g -c -Wall main.c 
arbres.o: arbres.c interface.h memoire.h arbres.h  makefile
	gcc -g -c -Wall arbres.c
memoire.o: memoire.c memoire.h  makefile
	gcc -g -c -Wall memoire.c
interface.o: interface.c interface.h makefile
	gcc -g -c -Wall interface.c
clean:	
	rm abr *.o
#---------------------fin makefile--------------------------
