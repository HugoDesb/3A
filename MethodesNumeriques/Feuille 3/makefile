main: exo.o main.o
	gcc -o main exo.o main.o

exo.o: exo.c
	gcc -o exo.o -c exo.c -W -Wall -pedantic


main.o: main.c feuille3.h
	gcc -o main.o -c main.c -W -Wall -pedantic