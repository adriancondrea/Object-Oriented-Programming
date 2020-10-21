#include "controller.h"
#include <stdlib.h>
#include <string.h>
Service* createService(Repository* repository)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (service == NULL)
		return NULL;
	service->repository = repository;
	return service;
}

void destroyService(Service* service)
{
	destroyRepository(service->repository);
	free(service);
}

/*creates gear with given fields and calls the addGear function from repository, returning its result
returns 1 if gear with given catalogue number already exists, 0 otherwise*/
int addGearService(Service* service, int catalogueNumber, char* state, char* type, int value)
{
	Gear gearItem = createGear(catalogueNumber, state, type, value);
	return addGear(service->repository, gearItem);
}

/* returns 1 if gear with given catalogue number does not exist, 0 otherwise*/
int removeGearByCatalogueNumberService(Service* service, int catalogueNumber)
{
	return deleteGearByCatalogueNumber(service->repository, catalogueNumber);
}

int updateGearByCatalogueNumberService(Service* service, int catalogueNumber, char* newState, char* newType, int newValue)
{
	return updateGearByCatalogueNumber(service->repository, catalogueNumber, newState, newType, newValue);
}

/* returns a pointer to a vector that contains all gear elements */
vector* getAllGearService(Service* service)
{
	return getAllGear(service->repository);
}

vector* filterSmallerThanValueService(Service* service, int value)
{
	return filterSmallerThanValue(service->repository, value);
}

/* function that sorts the gearList of a vector ascending by state, using selection sort*/
void sortVectorByState(vector* GearVector)
{
	int i, j, length, minimumIndex;
	length = GearVector->currentLength;
	Gear* minimum;
	Gear auxiliaryGearItem;
	for (i = 0; i < length - 1; i++)
	{
		minimum = &GearVector->gearList[i];
		minimumIndex = i;
		for(j=i+1; j< length; j++)
			if (strcmp(getState(minimum), getState(&GearVector->gearList[j])) > 0)
			{
				minimum = &GearVector->gearList[j];
				minimumIndex = j;
			}
		if (minimumIndex != i)
		{
			copyGear(&auxiliaryGearItem, GearVector->gearList[i]);
			copyGear(&GearVector->gearList[i], GearVector->gearList[minimumIndex]);
			copyGear(&GearVector->gearList[minimumIndex], auxiliaryGearItem);
		}
	}

}

int undoService(Service* service)
{
	return undo(service->repository);
}

int redoService(Service* service)
{
	return redo(service->repository);
}
