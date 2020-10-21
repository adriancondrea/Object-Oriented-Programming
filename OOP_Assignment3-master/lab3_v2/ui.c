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
	Gear* gearList;
	Gear element;
	int length, index;
	gearList = getAllGearService(ui->service);
	length = getGearListLengthService(ui->service);
	for (index = 0; index < length; index++)
	{
		element = gearList[index];
		printf("%d %s %s %d\n", element.catalogueNumber, element.state, element.type, element.value);
	}
}

/*lists all gear elements with given type. Parses the entire list and prints only the elements with given type*/
void listType(UI* ui, char* type)
{
	Gear* gearList;
	Gear element;
	int length, index;
	gearList = getAllGearService(ui->service);
	length = getGearListLengthService(ui->service);
	for (index = 0; index < length; index++)
	{
		element = gearList[index];
		type = strtok(type, "\n");	//remove the newline from the end of the type
		if(strcmp(element.type, type) == 0)
			printf("%d %s %s %d\n", element.catalogueNumber, element.state, element.type, element.value);
	}
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
				type = parameters[0];
				listType(ui, type);
			}
		else printf("invalid command!\n");
	}
}
