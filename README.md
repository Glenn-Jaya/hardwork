## Files the marker should have:

*Note all of the non test h files should have a description at the top*

* Makefile
* README
* main.c
* hardwork .c and .h
	* Code relating to the hard\_work function and calculation of timing duration
* util .c and .h
	* small helper functions to handle/validate run time args
* manager.c and .h
	* Handles manipulation of an encapsulated array that holds ids of processes or threads in a safe manner.
	* Contains logic to safely start and end given work on each element of this array.
* processes.c and .h
	* Initiates process code and implements forking and waiting on the child
* threads.c and .h
	* Initiates thread code and implements thread creation and waiting on the thread
* tests/ folder
	* Makefile
	* main.c
	* minunit.h
	* testManager .c and .h
	* testUtil .c and .h

## Compile

```
make
```

Note do not use the above command within the tests/ folder as that has its own makefile.
The above command produces 2 executables: processes.out and threads.out


## Run Pgms

```
./processes.out x y

./threads.out x y
```

Where x is the total number of threads/processes to run.
Where y is the maximum number of threads/processes you want to be able to run at the same time/concurrently.

## Batch Pgms

We were told we can do this assignment in two ways and that make should only produce 2 executables. See the report for details. But I decidied I wanted to do both options and see which is faster. 

## Compile/create batch executables

```
make batch
```
This produces 2 more executables procBatch.out and threadBatch.out

To run those do:

```
./procBatch.out x y

./threadBatch.out x y
```

Where x and y is the same as the regular non batch executables.

## Clean

```
make clean
```

Make produces a lot of intermediary files for the linker.
This command removes everything but the listed files at the top of this README in the current directory.
Do note that the tests/ folder has its own make clean rule.


## Unit Tests

The project used TDD, as such you can use the tests for documentation if necessary.
To compile and run the tests you can run from anywhere:
```
make test
```

Alternatively you can type make from inside the tests/ folder to compile and run the tests
```
# INSIDE tests/ folder!
make
```

# Hypothesis

I think processes will take longer to create.
The reason why I think this is because the heap/memory is the same for all threads but if you create a new process you have to 
