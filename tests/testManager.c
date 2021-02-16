#include "testManager.h"
#include "minunit.h"
#include "../manager.h"

char * test_new_manager()
{
	int xx = 10;
	idManager manager = newIdManager(xx);	
	mu_assert("error with newManager in manager.c", isValidSize(manager)==true);
	return 0;
}
