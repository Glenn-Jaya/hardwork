#include "minunit.h"
#include "tests.h"

char * test_add()
{
	mu_assert("error with add", 2+2==4);
	return 0;
}


char * test_minus()
{
	        mu_assert("error with minus", 5-2==3);
		        return 0;
}
