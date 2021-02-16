#include "manager.h"

struct idHandler
{
	int maxLength;
	int currLength;
	int *data;
};


// Precondition: maxSize is not negative
// Postcondition: 
// 	* non null idManager returned
// 	* int array initialized with all -1
idManager newIdManager(int maxSize)
{
	// should never be neg here because handleArgs func in util.c deals with that
	assert (maxSize > 0);
	idManager manager = (idManager) malloc(sizeof(idManager));
	assert(manager != NULL);

	manager->data = (int*)malloc(maxSize*sizeof(int));
	assert(manager->data != NULL);

	for (int i = 0; i < maxSize; i++)
	{
		manager->data[i] = -1;
	}

	manager -> currLength = 0;
	manager ->maxLength = maxSize;

	return manager;
}

// precondition:
// 	* idManager received is valid
// 	* id is positive
// postcondition: return true only when array successfully updated with new id
// invariant: valid length of struct

bool addID(idManager manager, int id)
{
	assert(manager!=NULL);

	// decided to return bool if not valid length instead of asserts
	/*assert(id>-1);*/
	/*assert(isValidSize(manager));*/

	int currLen = manager->currLength;
	int maxLen = manager->maxLength;
	// if neg id, maybe fork return -1
	if (isValidSize(manager)&&id>-1&&
			currLen < maxLen)
	{
		manager -> data[currLen] = id;
		manager -> currLength++;
		if (isValidSize(manager))
			return true;
	}
	return false;
}


idManager destroyManager(idManager manager)
{
	if (manager != NULL)
	{
		if (manager->data != NULL)
		{
			free(manager->data);
		}
		free(manager);
	}
	return NULL;
}

// Our invariant for this struct. Should check when we insert/delete.
// note when add last element, currLen = maxLength so it's valid
bool isValidSize(idManager manager)
{
	bool validSize = true;

	int cL = manager->currLength;
	int maxL = manager->maxLength;

	if (cL > maxL)
		validSize = false;
	if (cL < 0)
		validSize = false;

	return validSize;
}
