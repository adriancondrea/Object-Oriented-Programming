#pragma once
#include "repository.h"

typedef struct
{
	Repository* repository;
}Service;

Service* createService(Repository* repository);
void destroyService(Service* service);
int addGearService(Service* service, int catalogueNumber, char* state, char* type, int value);
int removeGearByCatalogueNumberService(Service* service, int catalogueNumber);
int updateGearByCatalogueNumberService(Service* service, int catalogueNumber, char* newState, char* newType, int newValue);
Gear* getAllGearService(Service* service);
int getGearListLengthService(Service* service);