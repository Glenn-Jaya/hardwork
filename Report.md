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

***-1 row actually had the fork failed***

Note that this python script ran each row of the above table 3 times and took the average of the 3 to average out the differences.

It's a little hard to understand the data so what I did was I made graphs, where y axis is number of seconds, x axis is max concurrent threads.

### X = 100 for Processes

![x=100 for P with Python](https://i.imgur.com/znTsUCb.png)

**Note the above graph is plotting the nanoseconds, notice for y = 4 it is 2 sec the rest are 1 sec so initially the graph starts high not low.

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

## Results

So actually I did not have to worry, even though the python trials took longer (maybe something to do with pythons subprocess module) the trends were like the ones for the directly execution trials on the second table.

For the same total number of processes/threads increasing the maximum concurrent threads seems initially drasitically decrease execution time but up to a certain point/threshold. Then there is a slight trend of increasing execution time, for some it is so slight that it looks like a flat fline on the graph.

When you incrase the max number of processes/threads, the time it takes increases.

Fork fails when you try to run 500 concurrent processes. I tried it with -DBATCH as well, had the same thing happen.

## Analysis of Results/Questions

### Which is faster?

From these results it appears creating threads is faster than processes that run hardwork.

### Do your results match your hypothesis? Why or why not?

Yes these results match my hypotehsis.

The reason why it is more costly to create processes is related to the fact that threads share the same address space and share the same memory. However with processes the OS must create an indepedent address space for each process, consequently their data is not shared. It is also costly because the OS has to allocate memory each time we create a process but threads will re-use the existing heap, we are allocating more memory with processes every time we create it. And the more proceses you create the more costly it gets.

Proof of how costly this is when we tried to run processes.out with x = 1000 and y = 1000:

```
created work, total created: 508
created work, total created: 509
fork failed
```

The fork fails when we do not have enough resources to do a fork.
The address space is just a series of memory locations that can be accessed by an address.
So when we are creating processes the OS make this new section of memory and at some point we run out of memory to allocate. But we are able to run x = 1000 and y = 1000 threads just fine because the OS is not making entirely new contiguous memory locations like with processes because we want the processes to have private memory. Again threads share the same address space.

I also have another theory why processes are more costly. In the textbook it goes on a tangent about file descriptors, showing how you can fork and the child inherits the parents file descriptor. But if you close the child file descriptor it does not also close the parents file descriptor. This initialization of I/O for processes is done by the OS. But threads share file descriptors because multiple threads are in 1 process. So when we are creating processes I think this is another reason why it is more costly but is not mentioned in great detail in the textbook. 

This project is very similar to threadpools where some main service calls worker threads to run some work. The processes side of this project is the same thing but uses processes to create parallelism where part of the code is run on each cpu core.

### Is there a point of diminishing returns?

As noted by the graphs, at first increasing the max concurrent number of threads exponentially reduces execution time but there seems to be a point where increasing the number of maximum concurrent threads/processes has little benefit and infact starts to increase. 

My results give me an indication that I need to pursue this increase further. So lets do threads with X = 10000 to see if it gives further proof of our theory:

| x     | y     | nanoseconds |
|-------|-------|-------------|
| 10000 | 5     | 406609048   |
| 10000 | 10    | 108936762   |
| 10000 | 15    | 738614222   |
| 10000 | 20    | 151995696   |
| 10000 | 200   | 150323089   |
| 10000 | 500   | 160558462   |
| 10000 | 1000  | 168927591   |
| 10000 | 2000  | 179349718   |
| 10000 | 5000  | 219546561   |
| 10000 | 8000  | 253606674   |
| 10000 | 10000 | 320055614   |

And here is a graph for X is 10000 threads:

![10000](https://i.imgur.com/5xseGLw.png)

Ok so somewhere between 10 and 15 it went from the time to falling to rising and we keep rising till we reach y = 10000!

The reason for this is due to Amdahl's law. At some point we can not parallelize this program any further and all we have left is the serialized part of this project. At first it was easy to break this program apart into chunks that could be run in parrallel similar to an embarassingly parellel program but as the program went on there is less and less benefit to parrallelizing the problem. In fact between 10 and 15 max concurrent there appears to be an increase cost. Remember the number of cores for this machine is 12 and this is probably the point at where this change occurs. 

If I run with y = 11, nanoseconds is only 40 million. But if I run with y = 12, nanoseconds jumps to 800 million.

So we just confirmed this threshold point is at 12. Therefore there is an optimal max of threads to run this program.

Now lets think about this from the perspective of a OS. How is it possible to run 15 threads if we only have 12 cores? The OS does swapping of this thread on that core really fast to virtualize/give the illusion that 15 threads are actually running at once.

What happens when you switch between threads? A context switch! So it becomes more costly because the OS has to save all the state of this thread in registers than load the register of the other thread and keep repeating this process. This process is a linear/serial one, we are increasing the cost of this serieal problem the more threads we have and therefore increasing the cost of the program as a whole as we keep increasing the threads after the threshold point.

## Bonus

Note I could not do the bonus because I didn't have a mac computer with an OS version high enough to run the profiler timer code, you need like Mac OS 10.2
