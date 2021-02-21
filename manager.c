#include "manager.h"

// this struct is not defined in the .h to provide encapsulation
// for example other c files do not know anything about the vars inside and can't access directly
// 	they only know about the ptr in header.
// 	fun way to sort of provide Object O
struct idHandler
{
	int maxLength;
	int currLength;
	dataType *data;
};


// Precondition: maxSize is not negative
// Postcondition: non null and valid sized idManager returned
// Invariant: idManager is validSize
idManager newIdManager(int maxSize)
{
	// should never be neg here because handleArgs func in util.c deals with that
	assert (maxSize > 0);

	idManager manager = (idManager) malloc(sizeof(idManager));
	assert(manager != NULL);

	manager->data = (dataType*)malloc(maxSize*sizeof(dataType));
	assert(manager->data != NULL);

	manager -> currLength = 0;
	manager ->maxLength = maxSize;

	assert(isValidSize(manager));

	return manager;
}

// Adds into array but note it also increments currLength
// 	so we are keeping track of how much we are adding as well!
// precondition: idManager received is valid
// postcondition: return true only when array successfully updated with new id
// invariant: manager is the correct size before insert and after

bool addID(idManager manager, dataType id)
{
	assert(manager!=NULL);

	int currLen = manager->currLength;
	int maxLen = manager->maxLength;

	if (isValidSize(manager) && currLen < maxLen)
	{
		manager -> data[currLen] = id;
		manager -> currLength++;
		if (isValidSize(manager))
			return true;
	}

	return false;
}


// precondition: manager and data not null
// postcondition: after free pointers set to null
idManager destroyManager(idManager manager)
{
	if (manager != NULL)
	{
		if (manager->data != NULL)
		{
			free(manager->data);
			manager->data = NULL;
		}
		free(manager);
		manager = NULL;
	}
	return NULL;
}

// Our invariant for this struct. Should check when we insert/delete.
// note when add last element, currLen = maxLength so it's valid
// precondition: manager is not null
bool isValidSize(idManager manager)
{
	assert(manager!=NULL);

	bool validSize = true;

	int cL = manager->currLength;
	int maxL = manager->maxLength;

	if (cL > maxL)
		validSize = false;
	if (cL < 0)
		validSize = false;

	return validSize;
}


// main logic, every element added to array by addID() has work and endWork done to it
// 	ensures we always end the work not just start it and don't incorrectly access array :)
// precondition: 
// 	manager not null and correct size
// 	concurrent max is +'ve
// postconditon: manager is still valid by our invariant
void doWork(idManager manager, int maxConcurrent, 
		void (*work)(idManager, int*), void (*endWork)(dataType))
{
	assert(manager!=NULL);
	assert(isValidSize(manager));
	assert(maxConcurrent > 0);

	int amount = AMOUNT_OF_WORK;
	int concurrentCounter = 0;
	int numCreated = 0;
	int numRun = 0;
	int totalToRun = manager->maxLength;

	// timing code
	struct timespec beginClk;
	struct timespec endClk;
	struct timespec duration;	

	clock_gettime(CLOCK_REALTIME, &beginClk);

	while (numRun < totalToRun)
	{
		concurrentCounter = numCreated - numRun;
		while(concurrentCounter<maxConcurrent && 
				numCreated < totalToRun)
		{

			work(manager,&amount);
			concurrentCounter++;
			numCreated++;
			printf("created work, total created: %d\n",numCreated);
		}

#ifdef BATCH
		while (numRun < numCreated)
		{
#endif
			endWork(manager->data[numRun]);
			concurrentCounter--;
			numRun++;
			printf("ended work, total ended: %d\n",numRun);
#ifdef BATCH
		}
#endif
	}

	clock_gettime(CLOCK_REALTIME, &endClk);
	duration = diff(beginClk, endClk);
	printf("\n\nCompleted in: %ld seconds and %ld nanoseconds.\n\n", 
			duration.tv_sec, duration.tv_nsec);

	assert(isValidSize(manager));
}
