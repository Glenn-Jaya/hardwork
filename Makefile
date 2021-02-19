CC=clang
CFLAGS=-g -Wall -Wpedantic -Wextra -Werror

all: processes threads

%.o: %.h %.c
	$(CC) $(CFLAGS) -c $^

# note this recreates .o files but with the -DTHREADS flag
# there might be a better way but I don't know make well enough and this works :)
%.t: %.h %.c
	$(CC) $(CFLAGS) -DTHREADS -c $^

processes: main.c util.o hardwork.o manager.o processes.o
	$(CC) $(CFLAGS) -o $@.out $^

# unfortunately I can't use the $^ trick because the called rules don't match the .o files names
# ideally I'd prefer to replace util.t with util.o and then when call rule util.o pass the flag -DTHREADS
# again i don't know how to do that and for now this works
threads: main.c util.t hardwork.t manager.t threads.t
	$(CC) $(CFLAGS) -DTHREADS -lpthread -o $@.out main.c util.o hardwork.o manager.o threads.o

clean:
	rm -f *.out
	rm -f *.gch
	rm -f *.o

test:
	cd tests/ && make
