#include <iostream>
#include "UI.h"

void add_entries_at_startup(Controller& controller)
{
    controller.add_task(Task{"Solve_OOP_assignment", 120, 1});
    controller.add_task(Task{"Respond_to_emails", 45, 2});
    controller.add_task(Task{"Eat_sushi", 30, 3});
    controller.add_task(Task{"Visit_parent", 240, 1});
    controller.add_task(Task{"Buy_a_jacket", 120, 2});
}


int main()
{
    {
        Repository repository;
        Controller controller{ repository };
        add_entries_at_startup(controller);
        UI ui{ controller };

        ui.start_program();
    }

    return 0;
}
