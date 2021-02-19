CC=clang
CFLAGS=-g -Wall -Wpedantic -Wextra -Werror -fno-stack-protector

all: test

# this creates a util.o in the parent folder
util.o: ../util.h ../util.c
	cd ../ && $(CC) $(CFLAGS) -c util.h util.c && cp util.o tests/

manager.o: ../manager.h ../manager.c
	cd ../ && $(CC) $(CFLAGS) -c manager.h manager.c && cp manager.o tests/

hardwork.o: ../hardwork.h ../hardwork.c
	cd ../ && $(CC) $(CFLAGS) -c hardwork.h hardwork.c && cp hardwork.o tests/

testUtil.o: testUtil.c testUtil.h util.o
	$(CC) -c $^

testManager.o: testManager.c testManager.h manager.o
	$(CC) -c $^

testMath.o: testMath.c tests.h
	$(CC) -c $^

test: main.c testMath.o testUtil.o util.o testManager.o manager.o hardwork.o
	$(CC) $^ 
	./a.out

testgdb: main.c testMath.o testUtil.o util.o
	$(CC) $^ 
	gdb ./a.out

clean:
	rm -f *.o
	rm -f *.out
	rm -f *.gch
