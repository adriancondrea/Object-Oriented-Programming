#pragma once
#define MAXIMUM_DIMENSION 100
// the maximum dimension for state and type strings
// representation of gear element
typedef struct
{
	int catalogueNumber;
	char state[MAXIMUM_DIMENSION];
	char type[MAXIMUM_DIMENSION];
	int value;
} Gear;

Gear createGear(int catalogueNumber, char state[], char type[], int value);
int getCatalogueNumber(Gear gearItem);
int getValue(Gear gearItem);
char* getState(Gear* gearItem);
char* getType(Gear* gearItem);