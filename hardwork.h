// Description:
// 	* Code relating to the hard_work function and calculation of timing duration
// 	* Easier to mark because all of the code here is given by the assignment instructions
// 		so no need to mark hardwork.c or hardwork.h

#ifndef HARDWORK_H
#define HARDWORK_H 


#include <time.h>

void * hard_work(void *work);

struct timespec diff(struct timespec start, struct timespec end);

#endif //HARDWORK_H
