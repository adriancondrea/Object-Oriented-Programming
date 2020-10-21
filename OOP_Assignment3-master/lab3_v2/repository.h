#pragma once
#include "domain.h"
// define the repository, that can hold MAX_DIM elements
typedef struct
{
	Gear gearElemenets[MAXIMUM_DIMENSION];
	int length;
}Repository;

Repository* createRepository();
void destroyRepository(Repository* repository);
int findGearByCatalogueNumber(Repository* repository, int catalogueNumber);
int addGear(Repository* repository, Gear gearItem); 
int deleteGearByCatalogueNumber(Repository* repository, int catalogueNumber);
int updateGearByCatalogueNumber(Repository* repository, int catalogueNumber, char* newState, char* newType, int newValue);
Gear* getAllGear(Repository* repository);
int getGearListLength(Repository* repository);