#include <iostream>
#include <crtdbg.h>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){

		{
			testAll();
			testAllExtended();
		}

	_CrtDumpMemoryLeaks();

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
