#include "UI.h"

int main(int argc, char* argv[])
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