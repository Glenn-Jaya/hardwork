#include "testManager.h"
#include "minunit.h"
#include "../manager.h"

#include <stdio.h>

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

int workersCreated = 0;
int workersEnded = 0;

void workFunc(idManager manager, int* work)
{
	addID(manager,*work);
	workersCreated++;
}

void endFunc(pid_t id)
{
	workersEnded++;
}

char * test_do_work()
{
	int xx = 12;
	idManager manager = newIdManager(xx);	
	// get an error if maxConccurent is 0
	doWork(manager,3,workFunc,endFunc);
	destroyManager(manager);
	/*printf("WC: %d, WE: %d\n",workersCreated, workersEnded);*/
	mu_assert("error in doWork in manager.c", workersCreated == workersEnded);
	return 0;
}
