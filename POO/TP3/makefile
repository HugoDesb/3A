main: main.o
	g++ -o main main.o

main.o: ElementGen.gch PileGen.gch 
	g++ -o main.o -c main.cpp

ElementGen.gch: PileGen.gch
	g++ -o ElementGen.gch -c ElementGen.h

PileGen.gch: 
	g++ -o PileGen.gch -c PileGen.h
