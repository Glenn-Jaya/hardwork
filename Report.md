## Notes on Design

### Approach

#### Batch vs Singles

Dr Bristow on piazza said we could do this 2 way.

1. Launch x workers, wait for x workers to complete, then launch another x workers, or... 
2. Launch x workers, wait for 1 to complete and immediately launch another one, making sure you never go over x.

Initially my solution was written for option 2 (it is the executables you get when you type make) but I also created executables for option 1 (the executables you get when you type make batch).

If you do 
```
./processes.out 38 6
./procBatch.out 38 6
```

You see in both the 6 processes are created but afterwards procBatch.out the output is:

```
created work, total created: 6
ended work, total ended: 1
ended work, total ended: 2
ended work, total ended: 3
ended work, total ended: 4
ended work, total ended: 5
ended work, total ended: 6
created work, total created: 7
created work, total created: 8
created work, total created: 9
created work, total created: 10
created work, total created: 11
created work, total created: 12
ended work, total ended: 7
```

So here we are doing option 2, in batches where our batch size is y.

But if process.out does:

```
created work, total created: 6
ended work, total ended: 1
created work, total created: 7
ended work, total ended: 2
created work, total created: 8
ended work, total ended: 3
created work, total created: 9
ended work, total ended: 4
created work, total created: 10
ended work, total ended: 5
created work, total created: 11
ended work, total ended: 6
created work, total created: 12
ended work, total ended: 7
```

processes.out took around 11 million nano sec on my aviary machine and procBatch.out took around 16 or 17 mllion. 

For other numbers I entered, running it in batches seem to take a longer amount of time.
The same thrend is true for threads.out vs threadProc.out.

The only difference in the batch solutions and the non batch solutions is in manager.c:

```
#ifdef BATCH
                while (numRun < numCreated){
#endif
		// logic to end process/thread
		}
```

This actually shows the value of using these profiler for keeping track of the time, it proves/shows which implementation is faster and therefore less costly.
My guess as to why it is slower is that the cost of the individual instructions of this while loop simply costs more than it would ending the processes/threads 1 at a time. You are performing an addition numRun + 1 comparisions, plus 1 because because of the case where numRun = numCreated we still look at the condition to see if we should go into the while loop.Its cheaper to simply end the work and move on then doing these comparisons, ironically the lazy approach is the most cost effective approach.


#### No deletion, only insertion

In my solution we keep track of which thread/processes has been run/ended using an array.
This array is initiailzed by 'x' (runtime argument of number of total processes/threads).
Therefore we never are deleting from this array, only added into it and incrementing the indexes to this array.
We only care about the cumulative/total time of all the processes/threads run, we don not care which gets run first.

### Struct around array

C is not safe and does not provide objects therefore my design uses a struct to provide encapsulation around this array, maintains the indexes into this array, and handles safe adding of elements into this array. The rationale for this appraoch is so that other files that uses this struct do not have access to the array, they can not even read the array since they only have access to a pointer to this struct.

Do note the use of an invariant for this struct as well and DBC principles (pre and post conditions) used throughout the projeect.

### Amount of work

Note that the amount of work given to the hardwork function is defined as a constant in manager.h. The amount I put is 10. Note it does not really matter what value it is because we are comparing the difference between implementations. As long as it's constant it doesn't matter.

### IFDEF THREADS and function pointers

Originally I made this program for just processes with the intention of a seperate main file for threads.
But Dr Rasit informed us that we can use preprocessor code to specify whether we are doing threads or processes.
The benefit of this is that both threads and processes are using manager.c and therefore are using the same overarching logic for both.
This minimizes the amount of difference between the 2 executables produced which is important because we are interested in the difference between the two.

IFDEF THREADS were used in only 2 places. Once in main to decide whether to run the processes.c or threads.c code. The other is in manager.h so that the type the array stores can either be pid\_t (an int) or pthread\_t (unsigned long in this environement) at compile time.

Function pointers were also used (took inspiration from pthread\_create in man pages!) to provide modularity. To give an example from code:

```
void doWork(idManager manager, int maxConcurrent, 
	void (*work)(idManager, int*), void (*endWork)(dataType)); 
```

The 3rd argument is a pointer named work to a function that takes in an idManager and an int pointer (the amount of work which we defined as a constant) and returns void. That means we can pass in any function that takes in the same stuff and returns void! You can see this in testManager.c where i created my own simple work function. This makes the manager agnostic/independent of specific implementation. I could use this for another project that requires each element to have work done on.

The 4th argument shows how we are actually combining the IFDEF technique with the function pointer technique. At compile time dataType is replaced by whatever you specificy in manager's own .h file, therefore whatever type the array actually stores! I think this is a pretty neat and elegant solution.

