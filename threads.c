#include "hardwork.h"
#include "threads.h"

void threadWork(idManager threadManager, int* work)
{
	// allocate on heap, else lost when exit function
	pthread_t *workThread = (pthread_t *) malloc(sizeof(pthread_t));
	pthread_create(workThread, NULL, hard_work, work);
	addID(threadManager, workThread);	
}

void endThread(pthread_t *workThread)
{
	pthread_join(*workThread, NULL);
	free(workThread);
}

void runThreads(int totalProcesses, int maxConcurrent)
{
	idManager processManager = newIdManager(totalProcesses);
	doWork(processManager, maxConcurrent, threadWork, endThread);
	destroyManager(processManager);
}

