#ifndef MANAGER_H
#define MANAGER_H 

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// Purpose: Provide safe withdrawel/insertion into array of ints that represent ids
typedef struct idHandler *idManager;

// Purpose: Provide pseudo encapsulation by not defininng struct in header file

idManager newIdManager(int maxSize);


bool isValidSize(idManager manager);

#endif //MANAGER_H
