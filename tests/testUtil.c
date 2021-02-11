#include <stdbool.h>
#include "../util.h"
#include "tests.h"
#include "minunit.h"

char * test_valid_length()
{
	mu_assert("error with isValidLength in util.c", isValidLength(4)==true);
	mu_assert("error with isValidLength in util.c", isValidLength(3)==false);
	return 0;
}

char * test_valid_params()
{
	char** params;
	/*params = {"pgm Name","10000","-p","10"};*/
	params[0] = "pgmName";
	params[1] = "1000";
	params[2] = "-p";
	params[3] = "10";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==true);
	params[2] = "-t";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==true);
	params[2] = "p";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==false);
	/*params[1] = "asdf";*/
	params[3] = "i am cool";
	mu_assert("error with isValidParms in util.c", isValidParameters(params)==false);
	return 0;
}

char * test_string_is_number()
{
	mu_assert("error with isStringnUmber in util.c", isStringNumber("123")==true);
	mu_assert("error with isStringnUmber in util.c", isStringNumber("1a3")==false);

	return 0;
}
