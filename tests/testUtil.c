#include <stdbool.h>
#include <stdlib.h>
#include "../util.h"
#include "tests.h"
#include "minunit.h"

char * test_valid_length()
{
	mu_assert("error with isValidLength in util.c", isValidLength(3)==true);
	mu_assert("error with isValidLength in util.c", isValidLength(2)==false);
	return 0;
}

// TODO: If have time make each section its own seperate test run in main.c
char * test_valid_params()
{
	char** params = (char**)malloc(sizeof(char*)*3);
	params[0] = "pgmName";
	params[1] = "1000";
	params[2] = "10";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==true);

	// test not number
	params[2] = "i am cool";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==false);

	// reset
	params[2] = "10";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==true);
	params[1] = "1000";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==true);

	// test negative
	params[1] = "-1";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==false);
	params[1] = "1000";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==true);

	// test y > x
	params[2] = "1001";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==false);
	params[2] = "1000";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==true);


	free(params);
	return 0;
}

char * test_string_is_number()
{
	mu_assert("error with isStringnUmber in util.c", isStringNumber("123")==true);
	mu_assert("error with isStringnUmber in util.c", isStringNumber("1a3")==false);

	return 0;
}
