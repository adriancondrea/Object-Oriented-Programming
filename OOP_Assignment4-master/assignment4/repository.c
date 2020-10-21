#include "repository.h"
#include <stdlib.h>
#include <string.h>
Repository* createRepository()
{
	Repository* repository = (Repository*)malloc(sizeof(Repository));
	//if we couldn't allocate memory for the repository, return NULL
	if (repository == NULL)
		return NULL;
	// initialize the dynamic vector and allocate space for it
	repository->gearVector.capacity = DYNAMIC_VECTOR_CAPACITY;
	repository->gearVector.currentLength = 0;
	repository->gearVector.gearList = (Gear*) malloc(sizeof(Gear) * repository->gearVector.capacity);
	// set the undo and redo index to 0. We will use them to count the number of undos / redos left
	repository->redoIndex = 0;
	repository->undoIndex = 0;
	int index;
	// initialize the pointers of undoList and redoList to NULL, in order to know when to deallocate memory (the pointer is not NULL)
	for (index = 0; index < MAXIMUM_UNDO_REDO_STEPS; index++)
	{
		repository->undoList[index].gearList = NULL;
		repository->redoList[index].gearList = NULL;
	}
	return repository;
}
/*
returns a pointer to a dynamic array that contains all gear from gearList that have their value smaller than the parameter value
*/
vector* filterSmallerThanValue(Repository* repository, int value)
{
	vector* filteredGearList = (vector*) malloc(sizeof(vector));
	Gear* gearElement;
	filteredGearList->capacity = DYNAMIC_VECTOR_CAPACITY;
	filteredGearList->currentLength = 0;
	filteredGearList->gearList = (Gear*)malloc(sizeof(Gear) * filteredGearList->capacity);
	int index;
	for (index = 0; index < repository->gearVector.currentLength; index++)
	{
		gearElement = &repository->gearVector.gearList[index];
		if (getValue(*gearElement) < value)
		{
			if (filteredGearList->capacity == filteredGearList->currentLength)
				resize(filteredGearList);
			copyGear(&filteredGearList->gearList[filteredGearList->currentLength++], *gearElement);
		}
	}
	return filteredGearList;
}

/*save the state of vector source into vector destination*/
void saveState(vector* destination, vector* source)
{
	destination->capacity = source->capacity;
	destination->currentLength = source->currentLength;
	// if the gearList points to a valid memory location, we free it.
	if (destination->gearList != NULL)
		free(destination->gearList);
	// allocate space for the elements of source
	destination->gearList = (Gear*)malloc(sizeof(Gear) * destination->capacity);
	int index;
	// copy elements from source gearList to destination gearList one by one
	for (index = 0; index < destination->currentLength; index++)
		copyGear(&destination->gearList[index], source->gearList[index]);
}

/* changes the state of the gearVector from repository to a copy of the vector source
parameters: source - a vector storing a state
this function is used for undo and redo*/
void restoreState(Repository* repository, vector* source)
{
	repository->gearVector.capacity = source->capacity;
	repository->gearVector.currentLength = source->currentLength;
	free(repository->gearVector.gearList);
	repository->gearVector.gearList = (Gear*)malloc(sizeof(Gear) * repository->gearVector.capacity);
	int index;
	for (index = 0; index < repository->gearVector.currentLength; index++)
		copyGear(&repository->gearVector.gearList[index], source->gearList[index]);
}

/* performs undo using the undoList*/
int undo(Repository* repository)
{
	// if there is no operation to undo, return 1
	if (repository->undoIndex == 0)
		return ERROR;
	repository->undoIndex -= 1;
	// save the current state of the gearVector onto the redo list.
	saveState(&repository->redoList[repository->redoIndex++], &repository->gearVector);
	// restore the state stored in undoList.
	restoreState(repository, &repository->undoList[repository->undoIndex]);
	return ALL_GOOD;
}

/* performs redo using the redoList*/
int redo(Repository* repository)
{
	// if there is no operation to redo ( no previous undo), return 1
	if (repository->redoIndex == 0)
		return ERROR;
	repository->redoIndex -= 1;
	// save the current state onto the undo list, in order to be able to undo it
	saveState(&repository->undoList[repository->undoIndex++], &repository->gearVector);
	// restore the state saved onto the redo list
	restoreState(repository, &repository->redoList[repository->redoIndex]);
	return ALL_GOOD;
}

// frees the repository, as well as the gearLists stored in undo and redo vectors
void destroyRepository(Repository* repository)
{
	free(repository->gearVector.gearList);
	int index;
	index = 0;
	while (index < 20 && repository->undoList[index].gearList != NULL)
	{
		free(repository->undoList[index].gearList);
		index += 1;
	}
	index = 0;
	while (index < 20 && repository->redoList[index].gearList != NULL)
	{
		free(repository->redoList[index].gearList);
		index += 1;
	}
	free(repository);
}

/*returns -1 if the element with given catalogueNumber does not exist in the repository, or
the index of the element if it exists*/
int findGearByCatalogueNumber(Repository* repository, int catalogueNumber)
{
	int index;
	for (index = 0; index < repository->gearVector.currentLength; index++)
		if (getCatalogueNumber(repository->gearVector.gearList[index]) == catalogueNumber)
			return index;
	return NONEXISTENT;
}

/*
returns 1 if gear with given catalogue number already exists, otherwise adds the elements to the repository
and returns 0
*/
int addGear(Repository* repository, Gear gearItem)
{	
	if (findGearByCatalogueNumber(repository, gearItem.catalogueNumber) != NONEXISTENT)
		return ERROR;
	saveState(&repository->undoList[repository->undoIndex++], &repository->gearVector);
	if(repository->gearVector.capacity - repository->gearVector.currentLength == 0)
		resize(&repository->gearVector);
	repository->gearVector.gearList[repository->gearVector.currentLength++] = gearItem;
	return ALL_GOOD;
}

/*returns 1 if gear with given catalogue number does not exist, otherwise deletes the element from the list by
moving all elements to the right of it one position to the left, changes the length of the repository and returns zero*/
int deleteGearByCatalogueNumber(Repository* repository, int catalogueNumber)
{
	int indexOfGearToBeDeleted, index;
	indexOfGearToBeDeleted = findGearByCatalogueNumber(repository, catalogueNumber);
	if ( indexOfGearToBeDeleted == -1)
		return ERROR;
	saveState(&repository->undoList[repository->undoIndex++], &repository->gearVector);
	for (index = indexOfGearToBeDeleted; index < repository->gearVector.currentLength - 1; index++)
		repository->gearVector.gearList[index] = repository->gearVector.gearList[index + 1];
	repository->gearVector.currentLength--;
	return ALL_GOOD;
}

/*returns 1 if gear with given catalogue number does not exist, otherwise updates it*/
int updateGearByCatalogueNumber(Repository* repository, int catalogueNumber, char* newState, char* newType, int newValue)
{
	int indexOfGearToBeUpdated;
	indexOfGearToBeUpdated = findGearByCatalogueNumber(repository, catalogueNumber);
	if (indexOfGearToBeUpdated == -1)
		return ERROR;
	saveState(&repository->undoList[repository->undoIndex++], &repository->gearVector);
	strcpy(repository->gearVector.gearList[indexOfGearToBeUpdated].state, newState);
	strcpy(repository->gearVector.gearList[indexOfGearToBeUpdated].type, newType);
	repository->gearVector.gearList[indexOfGearToBeUpdated].value = newValue;
	return ALL_GOOD;
}

/*returns the address to the list of gear elements*/
vector* getAllGear(Repository* repository)
{
	return &repository->gearVector;
}

