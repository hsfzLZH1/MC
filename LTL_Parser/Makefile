lexer.h: lang.l
	flex lang.l

lexer.c: lang.l
	flex lang.l

parser.c: lang.y
	bison -o parser.c -d -v lang.y

parser.h: lang.y
	bison -o parser.c -d -v lang.y

lib.o: lib.c lib.h
	g++ -c lib.c

lang.o: lang.c lang.h lib.h
	g++ -c lang.c

parser.o: parser.c parser.h lexer.h lang.h
	g++ -c parser.c

lexer.o: lexer.c lexer.h parser.h lang.h
	g++ -c lexer.c

TS.o: TS.cpp
	g++ -c TS.cpp

main.o: main.cpp lexer.h parser.h lang.h
	g++ -c main.cpp

main: lang.o parser.o lexer.o lib.o TS.o main.o
	g++ lang.o parser.o lexer.o lib.o TS.o main.o -o main

all: main

clean:
	rm -f lexer.h lexer.c parser.h parser.c *.o main

%.c: %.y

%.c: %.l

.DEFAULT_GOAL := all

