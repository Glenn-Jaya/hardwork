#include "hardwork.h"

/*static void * hard_work(void *work)*/
void * hard_work(void *work)
{
	int *amount = (int*)work;
	struct timespec t = {.tv_sec = 0, .tv_nsec = *amount * 100000};
	nanosleep(&t,NULL);
	return NULL;
}
