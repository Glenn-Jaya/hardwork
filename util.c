#include "util.h"

// precondition:  argLength is a positive integer number greater than 0
// postconditions: only return true if arguments are valid
bool handleArgs(int argsLength, char** parameters)
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
	return true;
}

bool isValidLength(int length)
{
	if (length==3)
	{
		return true;
	}
	else
	{
		printf("\nYou have entered the wrong number of arguments, excluding the pgm name you need 2 arguments\n");
		return false;
	}

}

// helper function for isValidParameters preconditions, else hard to read
bool isString(char* possibleString)
{
	int length = strlen(possibleString);
	return possibleString[length]=='\0';
}


// precondition: parameters and its elements are not null, elements are strings (end in \0)
bool isValidParameters(char ** parameters)
{
	assert(parameters != NULL);
	assert(parameters[1] != NULL && isString(parameters[1]));
	assert(parameters[2] != NULL && isString(parameters[2]));

	char* total = parameters[1];
	if (!isStringNumber(total))
	{
		printf("\nthe 1st argument after pgm name must be a +'ve number\n");
		return false;
	}


	char* numAtSameTime = parameters[2];
	if (!isStringNumber(numAtSameTime))
	{
		printf("\nThe 2nd arg after pgm name must be a +'ve number\n");
		return false;
	}

	if (atoi(numAtSameTime) > atoi(total))
	{
		printf("\nThe 2nd arg after pgm name (y) must be <= than the 1st arg (x)\n");
		return false;
	}

	return true;
}

// note: negative numbers as strings are not considered numbers
// 	 we should not be having any negative numbers as input anyways
// precondition: string not null
bool isStringNumber(char* string)
{
	assert(string != NULL);
	int length = strlen(string);
	for (int i = 0; i < length; i++)
	{
		if (!isdigit(string[i]))
			return false;
	}
	return true;
}
