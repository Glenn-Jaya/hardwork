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

bool isValidSize(idManager manager)
{
	int cL = manager->currLength;
	int maxL = manager->maxLength;
	return cL<=maxL;
}
