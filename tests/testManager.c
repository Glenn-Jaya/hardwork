#include "testManager.h"
#include "minunit.h"
#include "../manager.h"

char * test_new_manager()
{
	int xx = 10;
	idManager manager = newIdManager(xx);	
	mu_assert("error with newManager in manager.c", isValidSize(manager)==true);
	destroyManager(manager);
	return 0;
}

char * test_add_id()
{
	int xx = 2;
	idManager manager = newIdManager(xx);	
	mu_assert("error in addID() in manager.c", addID(manager, 1)==true);
	mu_assert("error in addID() in manager.c", addID(manager, 2)==true);
	mu_assert("error in addID() in manager.c", addID(manager, 3)==false);
	mu_assert("error in addID() in manager.c", addID(manager, 4)==false);
	destroyManager(manager);
	idManager manager2 = newIdManager(xx);	
	mu_assert("error in addID() in manager.c", addID(manager2, 1)==true);
	mu_assert("error in addID() in manager.c", addID(manager2, -3)==false);
	destroyManager(manager2);
	return 0;
}
