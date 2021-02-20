## Files the marker should have:

*Note all of the non test h files should have a description at the top*

* Makefile
* README
* main.c
* hardwork .c and .h
	* Code relating to the hard_work function and calculation of timing duration
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
	* tests.h
	* testMath.c


## Compile

```
make
```

Note do not use the above command within the tests/ folder as that has its own makefile.
The above command produces 2 executables: processes.out and threads.out


## Run Pgms

```
./processes x y # for processes

./threads x y # for threads
```

Where x is the total number of threads/processes to run.
Where y is the maximum number of threads/processes you want to be able to run at the same time/concurrently.


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

## Notes on Design

### Approach

Dr Bristow said we could do this 2 way.

1. Run 1 processes/thread wait for that 1 to finish, then run the next.
2. Not run 1 at a time but run as a batch.

In my solution we run batches and keep track of which has been run/ended using an array.
This array is initiailzed by 'x' (runtime argument of number of total processes/threads).
Therefore we never are deleting from this array, only added into it and incrementing the indexes to this array.
We only care about the cumulative/total time of all the processes/threads run, we don't care which gets run first, therefore this batch approach is fine. Doing it the other way may add unneeded complexity and consequently be more error prone.

### Struct around array

C is not safe and does not provide objects therefore my design uses a struct to provide encapsulation around this array, maintains the indexes into this array, and handles safe adding of elements into this array. The rationale for this appraoch is so that other files that uses this struct do not have access to the array, they can't even read the array since they only have access to a pointer to this struct.

Do note the use of an invariant for this struct as well and DBC principles (pre and post conditions) used throughout the projeect.

### Amount of work

Note that the amount of work given to the hardwork function is defined as a constant in manager.h. The amount I put is 10. Note it doesn't really matter what value it is because we are comparing the difference between implementations. As long as it's constant it doesn't matter.

### IFDEF THREADS and function pointers

Originally I made this program for just processes with the intention of a seperate main file for threads.
But Dr Rasit informed us that we can use preprocessor code to specify whether we are doing threads or processes.
The benefit of this is that both threads and processes are using manager.c and therefore are using the same overarching logic for both.
This minimizes the amount of difference between the 2 executables produced which is important because we are interested in the difference between the two.

IFDEF THREADS were used in only 2 places. Once in main to decide whether to run the processes.c or threads.c code. The other is in manager.h so that the type the array stores can either be pid_t (an int) or pthread_t (unsigned long in this environement) at compile time.

Function pointers were also used (took inspiration from pthread_create in man pages!) to provide modularity. To give an example from code:

```
void doWork(idManager manager, int maxConcurrent,
                void (*work)(idManager, int*), void (*endWork)(dataType)); 
```

The 3rd argument is a pointer named work to a function that takes in an idManager and an int pointer (the amount of work which we defined as a constant) and returns void. That means we can pass in any function that takes in the same stuff and returns void! You can see this in testManager.c where i created my own simple work function. This makes the manager agnostic/independent of specific implementation. I could use this for another project that requires each element to have work done on.

The 4th argument shows how we are actually combining the IFDEF technique with the function pointer technique. At compile time dataType is replaced by whatever you specificy in manager's own .h file, therefore whatever type the array actually stores! I think this is a pretty neat and elegant solution.
