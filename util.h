// Description: small helper functions to handle/validate run time args

#ifndef UTIL_H
#define UTIL_H

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool handleArgs(int argsLength, char** parameters);

bool isValidLength(int length);
bool isValidParameters(char ** parameters);
bool isStringNumber(char* string);

#endif //UTIL_H
