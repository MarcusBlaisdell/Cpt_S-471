# Makefile for main

executable: main.o header.o
	g++ main.o header.o

main.o: main.cpp header.h
	g++ -c main.cpp

header.o: main.cpp header.h
	g++ -c main.cpp

clean:
	rm header.o main.o
