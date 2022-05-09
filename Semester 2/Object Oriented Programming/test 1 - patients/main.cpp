#include <iostream>
#include "UI.h"
#include <cassert>

void add_entries_at_startup(Controller& controller)
{
	controller.add_patient("Jessica_thompson", 42, false, "3", false);
	controller.add_patient("Lidia_aspen", 30, true, "3", true);
	controller.add_patient("Scott_smith", 86, false, "2", false);
	controller.add_patient("Zeno_hardy", 37, true, "8", false);
	controller.add_patient("Andrew_scott", 62, false, "2", false);
}

void test_controller()
{
	Repository repository;
	Controller controller{ repository };

	controller.add_patient("Jessica_thompson", 42, false, "3", false);
	controller.add_patient("Lidia_aspen", 30, true, "3", true);

	assert(controller.get_all_patients().size() == 2);

	bool removal_status = controller.remove_patient("Jessica_thompson");

	assert(removal_status == true);
	assert(controller.get_all_patients().size() == 1);

	removal_status = controller.remove_patient("Lidia_aspen");

	assert(removal_status == false);
	assert(controller.get_all_patients().size() == 1);
}

void test_controller_quarantine()
{
	Repository repository;
	Controller controller{ repository };

	controller.add_patient("Jessica_thompson", 42, false, "3", false);
	controller.add_patient("Lidia_aspen", 30, true, "3", true);
	controller.add_patient("Zeno_hardy", 37, true, "8", false);

	controller.quarantine_all();

	assert(controller.get_all_patients()[0].get_isQuarantined() == true);
	assert(controller.get_all_patients()[0].get_room_number() == "Q3");

	assert(controller.get_all_patients()[1].get_isQuarantined() == true);
	assert(controller.get_all_patients()[1].get_room_number() == "Q3");

	assert(controller.get_all_patients()[2].get_isQuarantined() == true);
	assert(controller.get_all_patients()[2].get_room_number() == "Q8");
}

int main()
{
	test_controller();
	test_controller_quarantine();

	Repository repository;
	Controller controller{ repository };
	add_entries_at_startup(controller);
	UI ui{ controller };

	ui.start_program();

	return 0;
}