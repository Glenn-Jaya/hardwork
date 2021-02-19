CC=clang
CFLAGS=-g -Wall -Wpedantic -Wextra -Werror

all: processes threads

%.o: %.h %.c
	$(CC) $(CFLAGS) -c $^

%.ot: %.h %.c
	$(CC) $(CFLAGS) -DTHREADS -c $^

processes: main.c util.o hardwork.o manager.o processes.o
	$(CC) $(CFLAGS) -o $@.out $^

threads: main.c util.ot hardwork.ot manager.ot threads.ot
	$(CC) $(CFLAGS) -DTHREADS -lpthread -o $@.out main.c util.o hardwork.o manager.o threads.o

clean:
	rm -f *.out
	rm -f *.gch
	rm -f *.o

test:
	cd tests/ && make
