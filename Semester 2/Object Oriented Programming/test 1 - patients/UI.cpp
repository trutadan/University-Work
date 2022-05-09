#include "UI.h"

#include <iostream>
#include <algorithm>
#include <sstream>

void UI::show_all_patients()
{
	std::vector<Patient> patients = this->controller.get_all_patients();

	auto sort_method = [](const Patient& patient1, const Patient& patient2) {
		return patient1.get_age() < patient2.get_age();
	};

	std::sort(patients.begin(), patients.end(), sort_method);

	for (const Patient& patient : patients)
		std::cout << patient.to_string() << "\n";
}

void UI::remove_patient_ui(const std::string& name)
{
	bool removal_status = this->controller.remove_patient(name);

	if (removal_status)
		std::cout << "The patient has been removed!\n";

	else
		std::cout << "The patient has not been removed!\n";
}

std::vector<std::string> split_command(const std::string& command, char separator) {
	std::vector<std::string> arguments;
	std::string argument;
	std::istringstream argumentStream(command);

	bool single_argument = true;
	while (std::getline(argumentStream, argument, separator)) {
		arguments.push_back(argument);
		single_argument = false;
	}

	if (single_argument)
		arguments.push_back(command);

	return arguments;
}

void print_menu()
{
	std::cout << "\n> remove,<name>\n";
	std::cout << "> show all\n";
	std::cout << "> quarantine\n";
	std::cout << "> exit\n";
}

void UI::start_program()
{
	std::vector<std::string> arguments;
	std::string command;

	std::cout << "Welcome to Infection speed Manager!\n";

	while (true) {
		print_menu();

		std::cout << "\n> ";
		std::getline(std::cin, command);
		arguments = split_command(command, ',');

		if (arguments.size() == 2 && arguments[0] == "remove")
			this->remove_patient_ui(arguments[1]);

		else if (arguments.size() == 1 && arguments[0] == "show all")
			this->show_all_patients();

		else if (arguments.size() == 1 && arguments[0] == "exit")
			break;

		else if (arguments.size() == 1 && arguments[0] == "quarantine")
			this->controller.quarantine_all();

		else
			std::cout << "Unknown command!\n";
	}

	std::cout << "Thank you for using our application!\n\n";
}
