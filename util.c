// small utility helper functions

#include <stdbool.h>
#include "util.h"

void handleArgs(int argsLength, char** parameters)
{
	printf("in handle args\n");
	printf("%d,%s\n",argsLength, parameters[0]); 
}

bool isValidLength(int length)
{
	printf("%d\n",length);
	/*return false;*/
	return true;
}
