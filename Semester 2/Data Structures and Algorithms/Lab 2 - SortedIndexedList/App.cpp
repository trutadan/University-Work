#include <iostream>
#include <crtdbg.h>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){

    system("Color 0A");

    {
        testAll();
        testAllExtended();
    }

    std::cout<<"Finished IL Tests!"<<std::endl;

    _CrtDumpMemoryLeaks;

	system("pause");
}