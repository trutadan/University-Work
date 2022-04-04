#include "UI.h"
#include "Tests.h"
#include <crtdbg.h>

int main() {
	test_all_functionalities();

	Repository* repository = create_repository();

	OperationStack* undo_stack = create_operation_stack();	
	OperationStack* redo_stack = create_operation_stack();

	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	add_estates_entries_at_application_startup(controller);

	UI* ui = create_ui(controller);

	run_program(ui);

	destroy_ui(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}