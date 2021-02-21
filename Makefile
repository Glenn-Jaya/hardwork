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


# BATCH STUFF SEE THE REPORT!!!
# Note it's not included in all rule because assignment said to produce 2 programs/executable when call make. It's a easter egg i guess :)

batch: procBatch threadBatch

%.bo: %.h %.c
	$(CC) $(CFLAGS) -DBATCH -c $^

%.bt: %.h %.c
	$(CC) $(CFLAGS) -DTHREADS -DBATCH -c $^

procBatch: main.c util.bo hardwork.bo manager.bo processes.bo
	$(CC) $(CFLAGS) -DBATCH -o $@.out main.c util.o hardwork.o manager.o processes.o

threadBatch: main.c util.bt hardwork.bt manager.bt threads.bt
	$(CC) $(CFLAGS) -DTHREADS -DBATCH -lpthread -o $@.out main.c util.o hardwork.o manager.o threads.o



clean:
	rm -f *.out
	rm -f *.gch
	rm -f *.o
	rm -f *.txt

test:
	cd tests/ && make
