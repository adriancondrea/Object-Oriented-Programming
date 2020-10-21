#pragma once
#include "controller.h"

typedef struct
{
	Service* service;
}UI;

UI* createUI(Service* service);
void destroyUI(UI* ui);
void addGearUI(UI* ui, int catalogueNumber, char* state, char* type, int value);
void updateGearByCatalogueNumberUI(UI* ui, int catalogueNumber, char* state, char* type, int value);
void deleteGearByCatalogueNumberUI(UI* ui, int catalogueNumber);
void listAllUI(UI* ui);
void listType(UI* ui, char* type);
void run(UI* ui);