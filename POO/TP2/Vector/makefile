main: main.o vector.o
	g++ vector.o main.o -o main

vector.o: vector.cpp vector.h
	g++ vector.cpp -c

main.o: main.cpp
	g++ main.cpp -c

clean: 
	rm *.o
