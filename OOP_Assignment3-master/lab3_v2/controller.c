#include "controller.h"
#include <stdlib.h>
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

Gear* getAllGearService(Service* service)
{
	return getAllGear(service->repository);
}

int getGearListLengthService(Service* service)
{
	return getGearListLength(service->repository);
}

