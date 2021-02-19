#include <stdio.h>
#include "util.h"
#include "processes.h"
#include "threads.h"

#ifdef THREADS
#define run runThreads
#endif

#ifndef THREADS
#define run runProcesses
#endif


int main(int argc, char** argv)
{
	if (handleArgs(argc, argv))
	{
		int total = atoi(argv[1]);
		int numAtSameTime = atoi(argv[3]);

		run(total,numAtSameTime);
	}
}
