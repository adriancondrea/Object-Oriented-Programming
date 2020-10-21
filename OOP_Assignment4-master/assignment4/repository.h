#pragma once
#include "domain.h"
// define the repository. Gear elements are saved in a dynamic array called vector. undoList and redoList are arrays that store objects of type
// vector, used for undo and redo functions. We save the state of gearVector after every operation that modifies it in undoList, and before every
// undo we save the state of gearVector in redoList.

typedef struct
{
	vector gearVector;
	vector undoList[MAXIMUM_UNDO_REDO_STEPS];
	vector redoList[MAXIMUM_UNDO_REDO_STEPS];
	int undoIndex, redoIndex;
}Repository;

Repository* createRepository();
void destroyRepository(Repository* repository);
int findGearByCatalogueNumber(Repository* repository, int catalogueNumber);
int addGear(Repository* repository, Gear gearItem); 
int deleteGearByCatalogueNumber(Repository* repository, int catalogueNumber);
int updateGearByCatalogueNumber(Repository* repository, int catalogueNumber, char* newState, char* newType, int newValue);
vector* getAllGear(Repository* repository);
vector* filterSmallerThanValue(Repository* repository, int value);
void saveState(vector* destination, vector* source);
void restoreState(Repository* repository, vector* source);
int undo(Repository* repository);
int redo(Repository* repository);