#ifndef HARDWORK_H
#define HARDWORK_H 

#include <time.h>

//static void * hard_work(void *work);
void * hard_work(void *work);

struct timespec diff(struct timespec start, struct timespec end);

#endif //HARDWORK_H
