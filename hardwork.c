#include "hardwork.h"

// all the code here is given so no need to mark this

void * hard_work(void *work)
{
	int *amount = (int*)work;
	struct timespec t = {.tv_sec = 0, .tv_nsec = *amount * 100000};
	nanosleep(&t,NULL);
	return NULL;
}

// from guyrutenberg's blog post linked in the assignment question
// if do more complicated timing code refactor to own timing file
struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
