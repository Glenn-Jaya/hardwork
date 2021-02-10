CC=clang
CFLAGS=-g -Wall -Wpedantic -Wextra -Werror

all: a1

util.o: util.h util.c
	$(CC) $(CFLAGS) -c $^

a1: main.c util.o
	$(CC) $(CFLAGS) -o $@.out $^

clean:
	rm -f *.out
	rm -f *.gch

test:
	cd tests/ && make
