all: main.cpp btree.h
	g++ -o main main.cpp -O0 -Wall -g


run:
	make
	./main
