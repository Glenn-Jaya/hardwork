// small utility helper functions

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"

// precondtion:  argLength is a positive integer number greater than 0
// postconditions: None because it returns void
void handleArgs(int argsLength, char** parameters)
{
	assert(argsLength>0);
	if (isValidLength(argsLength)==false || isValidParameters(parameters)==false)
	{
		printf("\n\nYou have incorrectly entered the command\n \
			you must enter in the form: \
			./a1.out x t y\n \
			where x = total number of threads or process\n \
			t = type so replace t with either -p or -t \n \
			and y = the number you want running at the same time\n");
		exit(1);
	}

}

bool isValidLength(int length)
{
	if (length==4)
	{
		return true;
	}
	else
	{
		printf("\nYou have entered the wrong number of arguments, excluding the pgm name you need 3 arguments\n");
		return false;
	}

}


bool isValidParameters(char ** parameters)
{
	char* total = parameters[1];
	if (!isStringNumber(total))
	{
		printf("\nthe 1st argument after pgm name must be a number\n");
		return false;
	}

	char* type = parameters[2];
	if (strcmp(type,"-p")!=0 &&  strcmp(type,"-t")!=0)
	{
		printf("\nThe 2nd arg after pgm name  must be -p or -t\n");
		return false;
	}

	char* numAtSameTime = parameters[3];
	if (!isStringNumber(numAtSameTime))
	{
		printf("\nThe 3nd arg after pgm name must be a number\n");
		return false;
	}

	return true;
}

bool isStringNumber(char* string)
{
	/*printf("%s\n",string);*/
	int length = strlen(string);
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(string[i]))
			return false;
	}
	return true;
}
