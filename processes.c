#include "hardwork.h"
#include "processes.h"

void childWork(idManager processManager, int* work)
{
	int id = fork();
	if (id<0)
	{
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	}
	if (id==0) // child
	{
		hard_work(work);
		exit(EXIT_SUCCESS);
	}
	addID(processManager, id);
}

void endChild(pid_t pid)
{
	printf("i am ending this: %d\n",pid);
	waitpid(pid,NULL,0);
}

void runProcesses(int totalProcesses, int maxConcurrent)
{
	idManager processManager = newIdManager(totalProcesses);
	doWork(processManager, maxConcurrent, childWork, endChild);
	destroyManager(processManager);
}
