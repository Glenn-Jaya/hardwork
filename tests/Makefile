CC=clang
CFLAGS=-g -Wall -Wpedantic -Wextra -Werror

all: test

# this creates a util.o in the parent folder
util.o: ../util.h ../util.c
	cd ../ && $(CC) $(CFLAGS) -c util.h util.c && cp util.o tests/

#testUtil.o: testUtil.c testUtil.h util.o
	#$(CC) -c testUtil.c testUtil.h ../util.o

#testUtil.o: testUtil.c testUtil.h util.o
	#$(CC) -c testUtil.c testUtil.h util.o

testUtil.o: testUtil.c testUtil.h util.o
	$(CC) -c $^

testMath.o: testMath.c tests.h
	$(CC) -c $^

#test: main.c testMath.o testUtil.o
	#$(CC) $^ ../util.o
	#./a.out

test: main.c testMath.o testUtil.o util.o
	$(CC) $^ 
	./a.out

testgdb: main.c testMath.o testUtil.o util.o
	$(CC) $^ 
	gdb ./a.out


clean:
	rm -f *.o
	rm -f *.out
	rm -f *.gch
