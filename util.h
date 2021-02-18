#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include "processes.h"

bool handleArgs(int argsLength, char** parameters);

bool isValidLength(int length);
bool isValidParameters(char ** parameters);
bool isStringNumber(char* string);



#endif //UTIL_H
