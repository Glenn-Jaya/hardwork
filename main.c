#include <stdio.h>
#include "util.h"

int main(int argc, char** argv)
{
	if (handleArgs(argc, argv))
	{
		int total = atoi(argv[1]);
		int numAtSameTime = atoi(argv[3]);

		runProcesses(total,numAtSameTime);
	}
}
