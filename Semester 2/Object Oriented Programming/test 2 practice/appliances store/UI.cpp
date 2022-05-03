#include "UI.h"

UI::UI()
{
	{}
}

UI::UI(Service _service)
{
	this->service = _service;
}

void UI::add_new_appliance()
{
	std::string id;
	double weight;

	std::cout << "Enter the appliance id: ";
	std::cin >> id;

	std::cout << "Enter the appliance weight: ";
	std::cin >> weight;

	std::string appliance_type;
	std::cout << "Enter the appliance type(dishwasher/refrigerator): ";
	std::cin >> appliance_type;

	if (appliance_type == "dishwasher") {
		double washing_cycle_length;
		double consumed_electricity_for_one_hour;

		std::cout << "Enter the dishwasher washing cycle length: ";
		std::cin >> washing_cycle_length;

		std::cout << "Enter the dishwasher consumed electricity for one hour: ";
		std::cin >> consumed_electricity_for_one_hour;

		Appliance* appliance;
		auto dishwasher = new DishWasher(id, weight, washing_cycle_length, consumed_electricity_for_one_hour);
		appliance = dishwasher;
		this->service.addAppliance(appliance);

		std::cout << "The new appliance has been successfully added!\n";
	}

	else if (appliance_type == "refrigerator") {
		std::string electricity_usage_class, has_freezer_string;

		std::cout << "Enter the refrigerator electricity usage class: ";
		std::cin >> electricity_usage_class;

		std::cout << "Does the refrigerator have freezer(true/false)? ";
		std::cin >> has_freezer_string;

		bool has_freezer;
		if (has_freezer_string == "true")
			has_freezer = true;

		else if (has_freezer_string == "false")
			has_freezer = false;

		else {
			std::cout << "Not a valid response! Try again.\n";
		}

		Appliance* appliance;
		auto refrigerator = new Refrigerator(id, weight, electricity_usage_class, has_freezer);
		appliance = refrigerator;
		this->service.addAppliance(appliance);

		std::cout << "The new appliance has been successfully added!\n";
	}

	else {
		std::cout << "Not a valid type! Try again.\n";
		return;
	}
}

void UI::display_all_appliances()
{
	std::cout << "Appliances:\n";
	for (auto& appliance : this->service.getAllAppliances())
		std::cout << appliance->toString() << "\n";
}

void UI::display_all_efficient_appliances()
{
	double filter_value;

	std::cout << "Enter the value of consumed electricity to filter the appliances: ";
	std::cin >> filter_value;

	std::cout << "Efficient Appliances:\n";
	for (auto& appliance : this->service.getAllWithConsumedElectricityLessThan(filter_value))
		std::cout << appliance->toString() << "\n";
}

void UI::save_to_file()
{
	double filter_value;

	std::cout << "Enter the value of consumed electricity to filter the appliances: ";
	std::cin >> filter_value;
	this->service.set_filterElectricity(filter_value);

	std::string file_name;

	std::cout << "Enter the name of the file: ";
	std::cin >> file_name;

	this->service.writeToFile(file_name);
}

void UI::populate_appliances()
{
	Appliance* appliance;
	auto dishwasher1 = new DishWasher("3", 35, 12, 15);
	appliance = dishwasher1;
	this->service.addAppliance(appliance);

	auto dishwasher2 = new DishWasher("12", 51, 16, 30);
	appliance = dishwasher2;
	this->service.addAppliance(appliance);

	auto refrigerator1 = new Refrigerator("5", 40, "A", true);
	appliance = refrigerator1;
	this->service.addAppliance(appliance);

	auto refrigerator2 = new Refrigerator("0", 101, "A++", false);
	appliance = refrigerator2;
	this->service.addAppliance(appliance);
}

void print_menu()
{
	std::cout << "1. Add new appliance.\n";
	std::cout << "2. Display all appliances.\n";
	std::cout << "3. Display all efficient appliances.\n";
	std::cout << "4. Save appliances to file.\n";
	std::cout << "5. Exit\n";
}

void UI::run_program()
{
	int command;
	populate_appliances();

	while (true) {
		print_menu();
		std::cout << "> ";

		std::cin >> command;

		switch (command) {
			case 1:
				this->add_new_appliance();
				break;

			case 2:
				this->display_all_appliances();
				break;

			case 3:
				this->display_all_efficient_appliances();
				break;

			case 4:
				this->save_to_file();
				break;

			case 5:
				return;
			
			default:
				std::cout << "Not a valid input! Try again.";
		}

	}
}

UI::~UI()
{
	{}
}
