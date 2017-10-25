all: main.cpp btree.h
	g++ -o main main.cpp -Wall -g


run:
	make
	./main
