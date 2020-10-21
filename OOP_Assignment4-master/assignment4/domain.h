#pragma once
#define MAXIMUM_DIMENSION 100
// the maximum dimension for state and type strings
#define MAXIMUM_UNDO_REDO_STEPS 20
// the maximum number of undo / redo steps our program can remember
#define DYNAMIC_VECTOR_CAPACITY 10
// the initial capacity of the dynamic vector
#define ERROR 1
#define ALL_GOOD 0
#define NONEXISTENT -1 
// representation of gear element
typedef struct
{
	int catalogueNumber;
	char state[MAXIMUM_DIMENSION];
	char type[MAXIMUM_DIMENSION];
	int value;
} Gear;

typedef struct
{
	Gear* gearList;
	int capacity;
	int currentLength;
} vector;

Gear createGear(int catalogueNumber, char state[], char type[], int value);
int getCatalogueNumber(Gear gearItem);
int getValue(Gear gearItem);
char* getState(Gear* gearItem);
void copyGear(Gear* destination, Gear source);
void resize(vector* gearVector);