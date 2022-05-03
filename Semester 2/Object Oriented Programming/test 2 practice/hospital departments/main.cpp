#include <iostream>
#include "UI.h"

int main()
{
	{
		Service service;
		UI ui{ service };
		ui.run_program();
	}
	
	_CrtDumpMemoryLeaks;

	system("pause");
	return 0;
}
