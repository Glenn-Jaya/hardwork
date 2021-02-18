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
	waitpid(pid,NULL,0);
}

/*void makeChildren(int totalChildren, int maxConcurrentChildren)*/
/*{*/
	/*int work = AMOUNT_OF_WORK;*/

	/*idManager processManager = newIDManager(totalChildren);*/

	/*int childrenCounter = 0;*/
	/*int concurrentCounter = 0;*/
	/*int numRun = 0;*/
	/*while (numRun < totalChildren)*/
	/*{*/
		/*while(concurrentCounter<maxConcurrentChildren)*/
		/*{*/
			/*childWork(&work);*/
			/*concurrentCounter++;*/
		/*}*/
		/*numRun++;*/
	/*}*/

	/*int maxRunningOnHardware = MAX_THREADS;*/
	/*if (numConcurrentChildren < MAX_THREADS)*/
		/*maxRunningOnHardware = numConcurrentChildren;*/

	/*for (int i = 0; i < maxRunningOnHardware; i++)*/
	/*{*/
		/*childWork(&work);*/
		/*concurrentCounter++;*/
	/*}*/
/*}*/



/*int main()*/
/*{*/
/*}*/
