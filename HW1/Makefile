all: main

main: main.o complex.o
	g++ main.o complex.o -o main

main.o: main.cpp complex.h
	g++ -c main.cpp -o main.о

complex.o: complex.cpp
	g++ -c complex.cpp -o complex.o

clean:
	rm *.o main
