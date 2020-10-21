#include "domain.h"
#include <string.h>
/*
creates gear with given fields
parameters:
	catalogueNumber - integer
	state - string maximum 100 characters
	type - string maximum 100 characters
	value - integer
*/
Gear createGear(int catalogueNumber, char state[], char type[], int value)
{
	Gear gearItem;
	gearItem.catalogueNumber = catalogueNumber;
	strcpy(gearItem.state, state);
	strcpy(gearItem.type, type);
	gearItem.value = value;
	return gearItem;
}

/*resizes the dynamic array pointed to by gearVector, doubling its capacity, allocating a new gearList double the size of the old one,
copying all elements and then deallocating the old gearList. */
void resize(vector* gearVector)
{
	Gear* newGearList;
	int newCapacity, index, gearListLength;
	newCapacity = gearVector->capacity * 2;
	newGearList = (Gear*)malloc(sizeof(Gear) * newCapacity);
	gearListLength = gearVector->currentLength;
	for (index = 0; index < gearListLength; index++)
		copyGear(&newGearList[index], gearVector->gearList[index]);
	free(gearVector->gearList);
	gearVector->gearList = newGearList;
	gearVector->capacity = newCapacity;
}

int getCatalogueNumber(Gear gearItem)
{
	return gearItem.catalogueNumber;
}

int getValue(Gear gearItem)
{
	return gearItem.value;
}

char* getState(Gear* gearItem)
{
	return gearItem->state;
}

/*
creates a copy of source gear item into destination gear item.
input: destination and source gear objects, destination provided by address and source by value
return: updates the destination gear item
*/
void copyGear(Gear* destination, Gear source)
{
	destination->catalogueNumber = source.catalogueNumber;
	strcpy(destination->state, source.state);
	strcpy(destination->type, source.type);
	destination->value = source.value;
}
