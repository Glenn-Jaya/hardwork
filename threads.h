#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include "manager.h"
/*
 * Functions used from manager.h:
 * 	addID(), newIdManager(),
 * 	doWork(), destoryManager()
 * 	*/

void threadWork(idManager threadManager, int* work);
void endThread(pthread_t *workThread);
void runThreads(int totalProcesses, int maxConcurrent);

#endif //THREADS_H
