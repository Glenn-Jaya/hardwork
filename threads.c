#include "hardwork.h"
#include "threads.h"

// note no need to validate threadManager, addID func does this for us :)
// precondition: work is not negative since negative work doesn't make sense.
// postcondition: thread creation succeeded checked, exit with failure if not.
void threadWork(idManager threadManager, int* work)
{
	assert(*work>=0);

	// allocate on heap, else lost when exit function
	pthread_t *workThread = (pthread_t *) malloc(sizeof(pthread_t));
	assert(workThread!=NULL);
	if(workThread==NULL)
	{
		fprintf(stderr, "malloc failed in threadWork\n");
		exit(EXIT_FAILURE);
	}

	int createVal = pthread_create(workThread, NULL, hard_work, work);
	assert(createVal == 0);
	if (createVal != 0)
	{
		fprintf(stderr, "pthreadCreate failed in threadWork\n");
		exit(EXIT_FAILURE);
	}
	addID(threadManager, workThread);
}

// precondition: workThread not null
// postcondition: join succeeded, if not we exit
void endThread(pthread_t *workThread)
{
	assert(workThread != NULL);

	int joinVal = pthread_join(*workThread, NULL);
	assert(joinVal == 0);
	if (joinVal != 0)
	{
		fprintf(stderr, "pthreadJoin failed in endThread\n");
		exit(EXIT_FAILURE);
	}

	free(workThread);
	workThread = NULL;
}

// purpose: create, start, destroy the manager that does all the logic and storage.
// precondition: totalThreads is positive and maxConcurrent is <= totalThreads
void runThreads(int totalThreads, int maxConcurrent)
{
	assert(totalThreads>0 && maxConcurrent <= totalThreads);

	idManager processManager = newIdManager(totalThreads);
	doWork(processManager, maxConcurrent, threadWork, endThread);
	destroyManager(processManager);
}
