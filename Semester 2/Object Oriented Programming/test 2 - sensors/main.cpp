#include <iostream>
#include "UI.h"


int main()
{
	{
		Device service{true};
		UI ui{ service };
		ui.runProgram();
	}

	system("pause");
	return 0;
}
