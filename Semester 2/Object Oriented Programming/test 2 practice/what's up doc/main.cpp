#include <iostream>
#include "UI.h"

int main()
{
    {
        Person person;
        UI ui{ person };
        ui.run_program();
    }
    _CrtDumpMemoryLeaks;
    system("pause");

    return 0;
}
