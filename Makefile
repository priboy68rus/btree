CFLAGS = -g -Wall -fprofile-arcs -ftest-coverage

all: main.cpp btree.h
	g++ ${CFLAGS} -o main main.cpp

clean:
	rm -rf *.g*

run:
	make clean
	make
	./main