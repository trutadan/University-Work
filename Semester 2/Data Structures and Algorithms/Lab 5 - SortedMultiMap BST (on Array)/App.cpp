#include <iostream>
#include <crtdbg.h>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
	{
		testAll();
		testAllExtended();
	}

	std::cout<<"Finished SMM Tests!"<<std::endl;
	_CrtDumpMemoryLeaks();
	
	system("pause");
}
