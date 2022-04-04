#include "Tests.h"
#include "UI.h"
#include "Functions.h"
#include <iostream>
#include <crtdbg.h>

int main()
{
    system("Color 0A");

        {
        test_all_functionalities();
        }
        
        {
        DynamicVector<Event>* repository_dynamic_vector = new DynamicVector<Event>;
        Repository* repository = new Repository(repository_dynamic_vector);

        DynamicVector<Event>* list_dynamic_vector = new DynamicVector<Event>;
        Repository* list = new Repository(list_dynamic_vector);

        DynamicVector<Event>* history_dynamic_vector = new DynamicVector<Event>;
        Repository* removal_history = new Repository(history_dynamic_vector);

        Controller* controller = new Controller(repository, list, removal_history);
        
        UI* ui = new UI(controller);

        ui->start_program();

        delete ui;
        delete controller;
        delete removal_history;
        delete history_dynamic_vector;
        delete list;
        delete list_dynamic_vector;
        delete repository;
        delete repository_dynamic_vector;
        }

    _CrtDumpMemoryLeaks();

    return 0;
}
