#ifndef MANAGER_H
#define MANAGER_H 

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "hardwork.h"

#define AMOUNT_OF_WORK 10

// Purpose: Provide safe withdrawel/insertion into array of ints that represent ids
typedef struct idHandler *idManager;

// Purpose: Provide pseudo encapsulation by not defininng struct in header file
idManager newIdManager(int maxSize);

idManager destroyManager(idManager manager);


bool isValidSize(idManager manager);

bool addID(idManager manager, int id);

void doWork(idManager manager, int maxConcurrent, void (*work)(idManager, int*), void (*endWork)(pid_t));

#endif //MANAGER_H
