#include <stdio.h>
#include "minunit.h"
#include "testUtil.h"
#include "testManager.h"

int tests_run = 0;

static char * all_tests()
{
	mu_run_test(test_valid_length);
	mu_run_test(test_valid_params);
	mu_run_test(test_string_is_number);
	mu_run_test(test_string_is_number);
	mu_run_test(test_new_manager);
	mu_run_test(test_add_id);
	mu_run_test(test_do_work);

        return 0;
}

int main (int argc, char **argv)
{
        char *result = all_tests();
        if (result!=0)
        {
                printf("Error. Test failed. Msg:%s\n", result);
        }
        else
        {
                printf("ALL TESTS PASSED! (%i total tests)\n",tests_run);
        }
        printf("Tests run: %d\n", tests_run);
        return result != 0;
}
