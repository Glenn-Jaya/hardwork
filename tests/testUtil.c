#include <stdbool.h>
#include "../util.h"
#include "tests.h"
#include "minunit.h"

char * test_valid_length()
{
	mu_assert("error with validLength in util", isValidLength(4)==true);
	return 0;
}
