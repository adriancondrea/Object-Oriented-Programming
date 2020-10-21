#include <assert.h>
#include "tests.h"

void createGear_validInput_createGear()
{
	Gear gearItem = createGear(1, "valid", "test", 2);
	assert(getCatalogueNumber(gearItem) == 1 && strcmp(getState(&gearItem), "valid") == 0 && strcmp(gearItem.type, "test") == 0 && getValue(gearItem) == 2);
}

void copyGear_validInput_copyGear()
{
	Gear item1 = createGear(1, "old", "test", 2);
	Gear item2 = createGear(3, "new", "asd", 4);
	copyGear(&item1, item2);
	assert(getCatalogueNumber(item1) == 3 && strcmp(getState(&item1), "new") == 0 && strcmp(item1.type, "asd") == 0 && getValue(item1) == 4);
}

void addGearService_addDuplicate_returnError()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 1, "abc", "def", 2);
	assert(addGearService(service, 1, "abc", "def", 2)==ERROR && repository->gearVector.currentLength == 1);
	destroyService(service);
}
void addGear_validInput_addGear()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 1, "abc", "def", 2);
	assert(repository->gearVector.currentLength == 1 && repository->gearVector.gearList[0].catalogueNumber == 1);
	destroyService(service);
}

void removeGearByCatalogueNumberService_valid_input_removeGear()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 1, "abc", "def", 2);
	removeGearByCatalogueNumberService(service, 1);
	assert(repository->gearVector.currentLength == 0);
	destroyService(service);
}
void updateGearByCatalogueNumberService_validInput_updateGear()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 1, "abc", "def", 2);
	updateGearByCatalogueNumberService(service, 1, "ghi", "jkl", 3);
	Gear element = repository->gearVector.gearList[0];
	assert(element.catalogueNumber == 1 && strcmp(element.state, "ghi") == 0 && strcmp(element.type, "jkl") == 0 && element.value == 3);
	destroyService(service);
}
void getAllGearService_validInput_getAllGear()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 1, "abc", "def", 2);
	vector* gearVector = getAllGearService(service);
	assert(gearVector->currentLength == 1 && gearVector->gearList[0].catalogueNumber == 1);
	destroyService(service);
}

void filterSmallerThanValueService_validInput_filter()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 1, "abc", "def", 2);
	addGearService(service, 2, "def", "jkl", 5);
	addGearService(service, 3, "ghi", "mno", 3);
	vector* filteredList = filterSmallerThanValueService(service, 4);
	assert(filteredList->currentLength == 2 && filteredList->gearList[0].catalogueNumber == 1 && filteredList->gearList[1].catalogueNumber == 3);
	free(filteredList->gearList);
	free(filteredList);
	destroyService(service);
}

void sortVectorByState_validInput_sortVector()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 5, "5", "5", 5);
	addGearService(service, 4, "4", "4", 4);
	addGearService(service, 3, "3", "3", 3);
	sortVectorByState(&repository->gearVector);
	assert(repository->gearVector.gearList[0].catalogueNumber == 3 && repository->gearVector.gearList[1].catalogueNumber == 4 && repository->gearVector.gearList[2].catalogueNumber == 5);
	destroyService(service);
}
void undoService_invalidInputNoUndos_returnError()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	assert(undoService(service) == ERROR);
	destroyService(service);
}

void redoService_invalidInputNoRedos_returnError()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	assert(redoService(service) == ERROR);
	destroyService(service);
}

void undoService_validInput_undo()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 5, "5", "5", 5);
	undoService(service);
	assert(repository->gearVector.currentLength == 0);
	destroyService(service);
}

void redoService_validInput_redo()
{
	Repository* repository = createRepository();
	Service* service = createService(repository);
	addGearService(service, 5, "5", "5", 5);
	undoService(service);
	redoService(service);
	assert(repository->gearVector.currentLength == 1 && repository->gearVector.gearList[0].catalogueNumber == 5);
	destroyService(service);
}
void test()
{
	createGear_validInput_createGear();
	copyGear_validInput_copyGear();
	addGear_validInput_addGear();
	addGearService_addDuplicate_returnError();
	removeGearByCatalogueNumberService_valid_input_removeGear();
	updateGearByCatalogueNumberService_validInput_updateGear();
	getAllGearService_validInput_getAllGear();
	filterSmallerThanValueService_validInput_filter();
	sortVectorByState_validInput_sortVector();
	undoService_invalidInputNoUndos_returnError();
	redoService_invalidInputNoRedos_returnError();
	undoService_validInput_undo();
	redoService_validInput_redo();
}