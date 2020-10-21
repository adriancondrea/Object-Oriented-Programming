#include "ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
UI* createUI(Service* service)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->service = service;
	return ui;
}

void destroyUI(UI* ui)
{
	destroyService(ui->service);
	free(ui);
}

void addGearUI(UI* ui, int catalogueNumber, char* state, char* type, int value)
{
	if (addGearService(ui->service, catalogueNumber, state, type, value) == 1)
		printf("No!\n");
}

void updateGearByCatalogueNumberUI(UI* ui, int catalogueNumber, char* state, char* type, int value)
{
	if (updateGearByCatalogueNumberService(ui->service, catalogueNumber, state, type, value) == 1)
		printf("No!\n");
}

void deleteGearByCatalogueNumberUI(UI* ui, int catalogueNumber)
{
	if (removeGearByCatalogueNumberService(ui->service, catalogueNumber) == 1)
		printf("No!\n");
}

void listAllUI(UI* ui)
{
	vector* gearVector;
	Gear element;
	int length, index;
	gearVector = getAllGearService(ui->service);
	length = gearVector->currentLength;
	for (index = 0; index < length; index++)
	{
		element = gearVector->gearList[index];
		printf("%d %s %s %d\n", element.catalogueNumber, element.state, element.type, element.value);
	}
}

/*lists all gear elements with given type. Parses the entire list and prints only the elements with given type*/
void listType(UI* ui, char* type)
{
	vector* gearVector;
	Gear element;
	int length, index;
	gearVector = getAllGearService(ui->service);
	length = gearVector->currentLength;
	for (index = 0; index < length; index++)
	{
		element = gearVector->gearList[index];
		type = strtok(type, "\n");	//remove the newline from the end of the type
		if(strcmp(element.type, type) == 0)
			printf("%d %s %s %d\n", element.catalogueNumber, element.state, element.type, element.value);
	}
}

void listGearWithValueSmallerThanGivenValue(UI* ui, int value)
{
	vector* filteredList = filterSmallerThanValueService(ui->service, value);
	// filter the list to contain only gear with value smaller than a given integer, then sort it and print it
	sortVectorByState(filteredList);
	Gear element;
	int index;
	for (index = 0; index < filteredList->currentLength; index++)
	{
		element = filteredList->gearList[index];
		printf("%d %s %s %d\n", element.catalogueNumber, element.state, element.type, element.value);
	}
	free(filteredList->gearList);
	free(filteredList);
}

void run(UI* ui)
{
	char userInput[MAXIMUM_DIMENSION];
	char *command, *parameters[4], *parameter;
	char* catalogueNumber, * state, * type, * value;
	// command - the first word from user input.
	// parameters - the next words after the command - we save maximum 4 words
	// parameter - used as auxiliary variable
	int numberOfParameters;
	while (1)
	{
		fgets(userInput, MAXIMUM_DIMENSION, stdin);
		if (strcmp(userInput, "exit\n") == 0)
			break;
		command = strtok(userInput, " ");
		numberOfParameters = 0;
		parameter = strtok(NULL, ",");
		while (parameter)
		{
			//remove spaces from the token
			while (parameter[0] == ' ')
				parameter = parameter + 1;
			parameters[numberOfParameters++] = parameter;
			parameter = strtok(NULL, ",");
		}
		char* catalogueNumber, * state, * type, * value;
		if (strcmp(command, "add") == 0)
			if (numberOfParameters != 4)
				printf("invalid parameters!");
			else
			{
				catalogueNumber = parameters[0];
				state = parameters[1];
				type = parameters[2];
				value = parameters[3];
				addGearUI(ui, atoi(catalogueNumber), state, type, atoi(value));
			}

		else if (strcmp(command, "update") == 0)
			if (numberOfParameters != 4)
				printf("invalid parameters!");
			else
			{
				catalogueNumber = parameters[0];
				state = parameters[1];
				type = parameters[2];
				value = parameters[3];
				updateGearByCatalogueNumberUI(ui, atoi(catalogueNumber), state, type, atoi(value));
			}
		else if (strcmp(command, "delete") == 0)
			if (numberOfParameters != 1)
				printf("invalid parameters!");
			else
			{
				catalogueNumber = parameters[0];
				deleteGearByCatalogueNumberUI(ui, atoi(catalogueNumber));
			}

		else if (strcmp(command, "list\n") == 0)
			listAllUI(ui);

		else if (strcmp(command, "list") == 0)
			if (numberOfParameters != 1)
				printf("invalid parameters!");
			else
			{
				value = parameters[0];
				listGearWithValueSmallerThanGivenValue(ui, atoi(value));
			}
		else if (strcmp(command, "undo\n") == 0)
			undoUI(ui);
		else if (strcmp(command, "redo\n") == 0)
			redoUI(ui);
		else printf("invalid command!\n");
	}
}

void undoUI(UI* ui)
{
	if (undoService(ui->service) == 1)
		printf("nothing to undo!\n");
}

void redoUI(UI* ui)
{
	if (redoService(ui->service) == 1)
		printf("nothing to redo!\n");
}
