#ifndef HARDWORK_H
#define HARDWORK_H 

#include <time.h>

// note a process can be thought of as 1 thread
#define MAX_THREADS 12
// amount is arbitrary, just keep consistent
#define AMOUNT_OF_WORK 10

//static void * hard_work(void *work);
void * hard_work(void *work);

#endif //HARDWORK_H
