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
vector* getAllGearService(Service* service);
vector* filterSmallerThanValueService(Service* service, int value);
void sortVectorByState(vector* GearVector);
int undoService(Service* service);
int redoService(Service* service);