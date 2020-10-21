#include "ui.h"
#include "controller.h"
#include "repository.h"
#include <stdio.h>
#include "tests.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main()
{
	test();
	Repository* repository = createRepository();
	Service* service = createService(repository);
	UI* ui = createUI(service);
	run(ui);
	destroyUI(ui);
	_CrtDumpMemoryLeaks();
	return 0;
}