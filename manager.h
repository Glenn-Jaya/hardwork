#ifndef MANAGER_H
#define MANAGER_H 

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "hardwork.h"

#define AMOUNT_OF_WORK 10

#ifdef THREADS
#define dataType pthread_t*
#endif

#ifndef THREADS
#define dataType pid_t
#endif

// Purpose: Provide safe withdrawel/insertion into array that contains ids
typedef struct idHandler *idManager;

// Purpose: Provide pseudo encapsulation by not defining struct in header file
idManager newIdManager(int maxSize);

idManager destroyManager(idManager manager);


bool isValidSize(idManager manager);

//bool addID(idManager manager, int id);
bool addID(idManager manager, dataType id);

void doWork(idManager manager, int maxConcurrent, 
		void (*work)(idManager, int*), void (*endWork)(dataType));

#endif //MANAGER_H
