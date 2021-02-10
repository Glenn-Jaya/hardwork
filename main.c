#include <stdio.h>
#include "util.h"

int main(int argc, char** argv)
{
	handleArgs(argc, argv);

	printf("argc: %d\n",argc);
	printf("argv:\n");
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d]: %s\n",i,argv[i]);
	}
}
