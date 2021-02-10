#include <stdio.h>
#include "minunit.h"
#include "tests.h"
#include "testUtil.h"

int tests_run = 0;

static char * all_tests()
{
        mu_run_test(test_add);
        mu_run_test(test_minus);
	mu_run_test(test_valid_length);
        return 0;
}

int main (int argc, char **argv)
{
        char *result = all_tests();
        if (result!=0)
        {
                printf("%s\n", result);
        }
        else
        {
                printf("ALL TESTS PASSED\n");
        }
        printf("Tests run: %d\n", tests_run);
        return result != 0;
}
