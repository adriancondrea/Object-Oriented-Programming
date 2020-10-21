#include "repository.h"
#include <stdlib.h>
Repository* createRepository()
{
	Repository* repository = (Repository*)malloc(sizeof(Repository));
	//if we couldn't allocate memory for the repository, return NULL
	if (repository == NULL)
		return NULL;
	repository->length = 0;
	return repository;
}

void destroyRepository(Repository* repository)
{
	free(repository);
}

/*returns -1 if the element with given catalogueNumber does not exist in the repository, or
the index of the element if it exists*/
int findGearByCatalogueNumber(Repository* repository, int catalogueNumber)
{
	int index;
	for (index = 0; index < repository->length; index++)
		if (getCatalogueNumber(repository->gearElemenets[index]) == catalogueNumber)
			return index;
	return -1;
}

/*
returns 1 if gear with given catalogue number already exists, otherwise adds the elements to the repository
and returns 0
*/
int addGear(Repository* repository, Gear gearItem)
{	
	if (findGearByCatalogueNumber(repository, gearItem.catalogueNumber) != -1)
		return 1;
	repository->gearElemenets[repository->length++] = gearItem;
	return 0;
}

/*returns 1 if gear with given catalogue number does not exist, otherwise deletes the element from the list by
moving all elements to the right of it one position to the left, changes the length of the repository and returns zero*/
int deleteGearByCatalogueNumber(Repository* repository, int catalogueNumber)
{
	int indexOfGearToBeDeleted, index;
	indexOfGearToBeDeleted = findGearByCatalogueNumber(repository, catalogueNumber);
	if ( indexOfGearToBeDeleted == -1)
		return 1;
	for (index = indexOfGearToBeDeleted; index < repository->length - 1; index++)
		repository->gearElemenets[index] = repository->gearElemenets[index + 1];
	repository->length--;
	return 0;
}

/*returns 1 if gear with given catalogue number does not exist, otherwise updates it*/
int updateGearByCatalogueNumber(Repository* repository, int catalogueNumber, char* newState, char* newType, int newValue)
{
	int indexOfGearToBeUpdated;
	indexOfGearToBeUpdated = findGearByCatalogueNumber(repository, catalogueNumber);
	if (indexOfGearToBeUpdated == -1)
		return 1;
	strcpy(repository->gearElemenets[indexOfGearToBeUpdated].state, newState);
	strcpy(repository->gearElemenets[indexOfGearToBeUpdated].type, newType);
	repository->gearElemenets[indexOfGearToBeUpdated].value = newValue;
	return 0;
}

/*returns the address to the list of gear elements*/
Gear* getAllGear(Repository* repository)
{
	return repository->gearElemenets;
}

int getGearListLength(Repository* repository)
{
	return repository->length;
}

