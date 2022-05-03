#include "UI.h"
#include <iostream>

UI::UI()
{
	{}
}

UI::UI(Person _person)
{
	this->person = _person;
}

void UI::add_new_measurement()
{
	std::string measurement_type, date;

	std::cout << "Enter the measurement type: ";
	std::cin >> measurement_type;

	if (measurement_type != "BMI") 
		if (measurement_type != "BP")
			throw std::exception("The type provided is not valid!");

	std::cout << "Enter the date: ";
	std::cin >> date;

	if (date.size() != 10)
		throw std::exception("The date must contain 10 characters!");

	if (measurement_type == "BP") {
		int systolic_value;
		std::cout << "Enter the systolic value: ";
		std::cin >> systolic_value;

		int diastolic_value;
		std::cout << "Enter the diastolic value: ";
		std::cin >> diastolic_value;

		auto BPMeasurement = new BP(date, diastolic_value, systolic_value);
		Measurement* measurement = BPMeasurement;

		this->person.addMeasurement(measurement);
		std::cout << "The measurement has been added!\n";

		if (measurement->isNormalValue())
			std::cout << "It is within the range of normal values!\n";

		else
			std::cout << "It is not within the range of normal values!\n";
	}

	else {
		double value;
		std::cout << "Enter the value of the BMI: ";
		std::cin >> value;

		auto BMIMeasurement = new BMI(date, value);
		Measurement* measurement = BMIMeasurement;
		
		this->person.addMeasurement(measurement);
		std::cout << "The measurement has been added!\n";

		if (measurement->isNormalValue())
			std::cout << "It is within the range of normal values!\n";

		else 
			std::cout << "It is not within the range of normal values!\n";
	}
}

void UI::display_all_measurements()
{
	std::cout << "Person: " << person.get_name() << "\n";

	for (auto& measurement : this->person.getAllMeasurements())
		std::cout << measurement->toString() << "\n";
}

void UI::is_person_healthy()
{
	int month;
	std::cout << "Enter the current month: ";
	std::cin >> month;

	if (person.isHealthy(month))
		std::cout << "The person is healthy!\n";

	else
		std::cout << "The person is not healthy!\n";
}

void UI::save_to_file()
{
	std::string file_name, date;
	
	std::cout << "Enter the date: ";
	std::cin >> date;

	if (date.size() != 10)
		throw std::exception("The date must contain 10 characters!");

	std::cout << "Enter the name of the file: ";
	std::cin >> file_name;

	this->person.writeToFile(date, file_name);
}

void UI::populate()
{
	Measurement* measurement;

	auto bmi_measurement1 = new BMI("2022.04.26", 20);
	measurement = bmi_measurement1;
	this->person.addMeasurement(measurement);

	auto bmi_measurement2 = new BMI("2022.05.02", 16);
	measurement = bmi_measurement2;
	this->person.addMeasurement(measurement);

	auto bmi_measurement3 = new BMI("2022.07.09", 27);
	measurement = bmi_measurement3;
	this->person.addMeasurement(measurement);

	auto bp_measurement1 = new BP("2022.02.15", 100, 80);
	measurement = bp_measurement1;
	this->person.addMeasurement(measurement);

	auto bp_measurement2 = new BP("2022.04.04", 110, 70);
	measurement = bp_measurement2;
	this->person.addMeasurement(measurement);
}

void print_menu()
{
	std::cout << "1. Add new measurement.\n";
	std::cout << "2. Display all measurements.\n";
	std::cout << "3. Is person healthy?\n";
	std::cout << "4. Save measurements to file.\n";
	std::cout << "5. Exit.\n";
}

void UI::run_program()
{
	int command;

	populate();

	while (true) {
		print_menu();

		std::cout << "> ";
		std::cin >> command;

		try {
			switch (command) {
			case 1:
				this->add_new_measurement();
				break;

			case 2:
				this->display_all_measurements();
				break;

			case 3:
				this->is_person_healthy();
				break;

			case 4:
				this->save_to_file();
				break;

			case 5:
				return;

			default:
				std::cout << "Not a valid input! Try again.\n";
			}
		}

		catch (const std::exception& e) {
			std::cout << e.what() << '\n';
		}
	}
}

UI::~UI()
{
	{}
}
