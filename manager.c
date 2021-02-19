#include "manager.h"

struct idHandler
{
	int maxLength;
	int currLength;
	dataType *data;
};


// Precondition: maxSize is not negative
// Postcondition: 
// 	* non null idManager returned
// 	* int array initialized with all -1
idManager newIdManager(int maxSize)
{
	// should never be neg here because handleArgs func in util.c deals with that
	assert (maxSize > 0);
	idManager manager = (idManager) malloc(sizeof(idManager));
	assert(manager != NULL);

	manager->data = (int*)malloc(maxSize*sizeof(dataType));
	assert(manager->data != NULL);

	for (int i = 0; i < maxSize; i++)
	{
		manager->data[i] = -1;
	}

	manager -> currLength = 0;
	manager ->maxLength = maxSize;

	return manager;
}

// precondition:
// 	* idManager received is valid
// 	* id is positive
// postcondition: return true only when array successfully updated with new id
// invariant: valid length of struct

bool addID(idManager manager, dataType id)
{
	assert(manager!=NULL);

	// decided to return bool if not valid length instead of asserts
	/*assert(id>-1);*/
	/*assert(isValidSize(manager));*/

	int currLen = manager->currLength;
	int maxLen = manager->maxLength;
	// if neg id, maybe fork return -1
	if (isValidSize(manager)&&id>-1&&
			currLen < maxLen)
	{
		manager -> data[currLen] = id;
		manager -> currLength++;
		if (isValidSize(manager))
			return true;
	}
	return false;
}


idManager destroyManager(idManager manager)
{
	if (manager != NULL)
	{
		if (manager->data != NULL)
		{
			free(manager->data);
		}
		free(manager);
	}
	return NULL;
}

// Our invariant for this struct. Should check when we insert/delete.
// note when add last element, currLen = maxLength so it's valid
bool isValidSize(idManager manager)
{
	bool validSize = true;

	int cL = manager->currLength;
	int maxL = manager->maxLength;

	if (cL > maxL)
		validSize = false;
	if (cL < 0)
		validSize = false;

	return validSize;
}

static void printData(idManager manager)
{
	for (int i = 0; i < manager->maxLength;i++)
	{
		printf("%d,",manager->data[i]);
	}
	printf("\n");
}

// idea: ifdef with function ptr endWork b/c param either pid_t or pthread_t
// idea: process.c and thread.c have own print function which we pass as func ptr to this function?
void doWork(idManager manager, int maxConcurrent, 
		void (*work)(idManager, int*), void (*endWork)(pid_t))
{
	int amount = AMOUNT_OF_WORK;
	int concurrentCounter = 0;
	int numRun = 0;
	int totalToRun = manager->maxLength;

	// timing code
	struct timespec beginClk;
	struct timespec endClk;
	struct timespec duration;	

	clock_gettime(CLOCK_REALTIME, &beginClk);

	while (numRun < totalToRun)
	{
		while((concurrentCounter+numRun) < totalToRun && 
				concurrentCounter<maxConcurrent)
		{

			work(manager,&amount);
			concurrentCounter++;
			printf("created work, total created: %d\n",numRun+concurrentCounter);
		}

		endWork(manager->data[numRun]);
		concurrentCounter--;
		numRun++;
		printf("ended work, total ended: %d\n",numRun);
	}

	clock_gettime(CLOCK_REALTIME, &endClk);
	duration = diff(beginClk, endClk);
	printData(manager);
	printf("\n\nCompleted in: %ld seconds and %ld nanoseconds.\n\n", 
			duration.tv_sec, duration.tv_nsec);
}
