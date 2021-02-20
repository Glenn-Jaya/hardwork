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

// Provide safe withdrawel/insertion into array that contains ids
typedef struct idHandler *idManager;

// Provide pseudo encapsulation by not defining struct in header file
idManager newIdManager(int maxSize);
idManager destroyManager(idManager manager);


// Invariant for idManager/struct
bool isValidSize(idManager manager);

// insert data into idManager
// manager does all the work, encapsulation 
// 	and whoever using it doesn't have to worry about how it works/implementation details
bool addID(idManager manager, dataType id);

// main logic, every element added to array by addID() has work and endWork done to it
// 	ensures we always end the work not just start it and don't incorrectly access array :)
void doWork(idManager manager, int maxConcurrent, 
		void (*work)(idManager, int*), void (*endWork)(dataType));

#endif //MANAGER_H
