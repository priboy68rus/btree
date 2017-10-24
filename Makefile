all: main.cpp btree.h
	g++ -o main main.cpp


run:
	make
	./main