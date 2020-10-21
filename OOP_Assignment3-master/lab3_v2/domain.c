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

char* getType(Gear* gearItem)
{
	return gearItem->type;
}