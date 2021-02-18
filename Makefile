CC=clang
CFLAGS=-g -Wall -Wpedantic -Wextra -Werror

all: a1

#util.o: util.h util.c
	#$(CC) $(CFLAGS) -c $^

%.o: %.h %.c
	$(CC) $(CFLAGS) -c $^

a1: main.c util.o hardwork.o manager.o processes.o
	$(CC) $(CFLAGS) -o $@.out $^

clean:
	rm -f *.out
	rm -f *.gch
	rm -f *.o

test:
	cd tests/ && make
