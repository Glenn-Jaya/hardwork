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

So here we are doing option 1, in batches where our batch size is y.

But process.out runs in singles (option 2):

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
The same trend is true for threads.out vs threadProc.out.

The only difference in the batch solutions and the non batch solutions is in manager.c:

```
#ifdef BATCH
                while (numRun < numCreated){
#endif
		// logic to end process/thread
#ifdef BATCH
		}
#endif
```

This actually shows the value of using these profiler for keeping track of the time, it proves/shows which implementation is faster and therefore less costly.
My guess as to why it is slower is that the cost of the individual instructions of this while loop simply costs more than it would ending the processes/threads 1 at a time. You are performing an additional numRun + 1 comparisions, plus 1 because because of the case where numRun = numCreated we still look at the condition to see if we should go into the while loop. Its cheaper to simply end the work and move on then doing these comparisons, ironically the lazy approach is the most cost effective approach.


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
The benefit of this is that both threads and processes are using manager.c and therefore are using the same overarching logic for both, they also print the exact same way.
This minimizes the amount of difference between the 2 executables produced which is important because we are interested in the difference between the two.

IFDEF THREADS were used in only 2 places. Once in main to decide whether to run the processes.c or threads.c code. The other is in manager.h so that the type the array stores can either be pid\_t (an int) or pthread\_t (unsigned long in this environement) at compile time.

Function pointers were also used (took inspiration from pthread\_create in man pages!) to provide modularity. To give an example from code:

```
void doWork(idManager manager, int maxConcurrent, 
	void (*work)(idManager, int*), void (*endWork)(dataType)); 
```

The 3rd argument is a pointer named work to a function that takes in an idManager and an int pointer (the amount of work which we defined as a constant) and returns void. That means we can pass in any function that takes in the same stuff and returns void! You can see this in testManager.c where i created my own simple work function. This makes the manager agnostic/independent of specific implementation. I could use this for another project that requires each element to have work done on.

The 4th argument shows how we are actually combining the IFDEF technique with the function pointer technique. At compile time dataType is replaced by whatever you specificy in manager's own .h file, therefore whatever type the array actually stores! I think this is a pretty neat and elegant solution.

---

## Experiments

Note that lscpu says we can run 12 threads on our cpus in total.
Keep in mind that 1 process can be thought of as just 1 thread of execution.
Therefore for my table i'm going to do 11, 12, 13 as well to see if anything happens at this breakpoint.

I have a python script called runexperiments.py and when I ran it I got the following results:

| Total p/t | y Concurrent p/t | Processes Sec | Processes NanoSec | Threads Sec | Threads Nanosec |
|-----------|------------------|---------------|-------------------|-------------|-----------------|
|         1 |                1 |             0 |           1546664 |           0 |         1330518 |
|       100 |                4 |             2 |         206374160 |           0 |        30810012 |
|       100 |                8 |             1 |         438477680 |           0 |        16444342 |
|       100 |               11 |             1 |         444003758 |           0 |        11904182 |
|       100 |               12 |             1 |         643031991 |           0 |        10976229 |
|       100 |               13 |             1 |         446218894 |           0 |         9978226 |
|       100 |               32 |             1 |         537533164 |           0 |         4829754 |
|       100 |               64 |             1 |         561068917 |           0 |         4222573 |
|       100 |              100 |             1 |         429370959 |           0 |         5574755 |
|      1000 |                4 |            25 |         322533255 |           0 |       309246554 |
|      1000 |                8 |            16 |         281340840 |           0 |       151002256 |
|      1000 |               11 |            15 |         238388271 |           0 |       107831249 |
|      1000 |               12 |            15 |         184792246 |           0 |        99502168 |
|      1000 |               13 |            15 |         596618968 |           0 |        92861871 |
|      1000 |               32 |            14 |         591322181 |           0 |        37816761 |
|      1000 |               64 |            14 |         599273519 |           0 |        18932290 |
|      1000 |              500 |            15 |         591167474 |           0 |        33408664 |
|      1000 |             1000 |            -1 |                -1 |           0 |        41912685 |

Note that this python script ran each row of the above table 3 times and took the average of the 3 to average out the differences.

It's a little hard to understand the data so what I did was I made graphs, where y axis is number of seconds, x axis is max concurrent threads.

### X = 100 for Processes

![x=100 for P with Python](https://i.imgur.com/znTsUCb.png)

### X = 100 for Threads

![x=100 for T with Python](https://i.imgur.com/8h2uoF7.png)

### X = 1000 for Processes

![x=1000 for P with Python](https://i.imgur.com/2CAmbC9.png)

### X = 1000 for Threads

![x=1000 for T with Python](https://i.imgur.com/ahII71p.png)


I also noticed that it took a little long to run this python script, I was concerned so I also ran all the trials individually like: ./processes.out 100 64. Did that for each row and the table I got was:

| Total p/t | Concurrent p/t | Processes Sec | Processes NanoSec  | Threads Sec | Threads Nanosec |
|-----------|----------------|---------------|--------------------|-------------|-----------------|
|         1 |              1 |             0 |            1901940 |           0 |         1410390 |
|       100 |              4 |             0 |           42295263 |           0 |        32991732 |
|       100 |              8 |             0 |           18246688 |           0 |        16525227 |
|       100 |             11 |             0 |           13664286 |           0 |        11820772 |
|       100 |             12 |             0 |           12495864 |           0 |        11374561 |
|       100 |             13 |             0 |           12407311 |           0 |         9562214 |
|       100 |             32 |             0 |            8834756 |           0 |         6559533 |
|       100 |             64 |             0 |            7819786 |           0 |         5262629 |
|       100 |            100 |             0 |            7734571 |           0 |         5752064 |
|      1000 |              4 |             0 |          398128816 |           0 |       308443795 |
|      1000 |              8 |             0 |          156755145 |           0 |       154497342 |
|      1000 |             11 |             0 |          112053083 |           0 |       112802952 |
|      1000 |             12 |             0 |          103779837 |           0 |        99213120 |
|      1000 |             13 |             0 |           95140488 |           0 |        85435687 |
|      1000 |             32 |             0 |           47316808 |           0 |        37304225 |
|      1000 |             64 |             0 |           48236510 |           0 |        23107904 |
|      1000 |            500 |             0 |           45679212 |           0 |        24174819 |
|      1000 |           1000 |             0 | fork failed at 509 |           0 |        24174819 |

I also made graphs for direct execution as well:


### X = 100 for Processes

![x=100 for P no Python](https://i.imgur.com/HOJ3ikG.png)

### X = 100 for Threads

![x=100 for T no Python](https://i.imgur.com/CcH4sWC.png)

### X = 1000 for Processes

![x=1000 for P no Python](https://i.imgur.com/CjKtVau.png)

### X = 1000 for Threads

![x=1000 for T no Python](https://i.imgur.com/uMO58Zz.png)



