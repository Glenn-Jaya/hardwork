#include "hardwork.h"
#include "processes.h"

// note no need to validate processManager, addID func does this for us :)
// precondition: work is not negative since negative work doesn't make sense.
// postcondition: fork succeeded, no assert since we exit if we failed!
void childWork(idManager processManager, int* work)
{
	assert(*work>=0);

	pid_t id = fork();
	if (id<0)
	{
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	}
	if (id==0) // child
	{
		hard_work(work);

		// without exit child we return twice, once for parent, once for child
		// but we don't want to return twice, just once for parent
		// else we'd increment the concurrentCounter of processes 
		// 	in manager.c's doWork func by 2 instead of 1 ruining my while loops
		// I think this might be why exec() never should return if it succeeds. Pretty neat.
		exit(EXIT_SUCCESS);
	}
	else // parent
	{
		addID(processManager, id);
	}
}

// precondition: pid is a positive value
// postcondition: pid waited is the expected pid
void endChild(pid_t pid)
{
	assert(pid>=0);
	// note i'm doing this NDEBUG thing because if compile with 
	// 	assertions off you'd get a unused var warning/error
#ifdef NDEBUG
	int returnedPID = waitpid(pid,NULL,0);
	assert(returnedPID==pid);
#endif
#ifndef NDEBUG
	waitpid(pid,NULL,0);
#endif
}

// purpose: create, start, destroy the manager that does all the logic and storage.
// precondition: totalProcesses is positive and maxConcurrent is <= totalProcesses
void runProcesses(int totalProcesses, int maxConcurrent)
{
	assert(totalProcesses>0 && maxConcurrent <= totalProcesses);

	idManager processManager = newIdManager(totalProcesses);
	doWork(processManager, maxConcurrent, childWork, endChild);
	destroyManager(processManager);
}
