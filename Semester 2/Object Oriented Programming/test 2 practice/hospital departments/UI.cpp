#include "UI.h"

UI::UI()
{
	{}
}

UI::UI(Service _service)
{
	this->service = _service;
}

void UI::add_new_department()
{
	std::string name, department_type;
	int number_of_doctors;

	std::cout << "Enter the department name: ";
	std::cin >> name;

	std::cout << "Enter the number of doctors: ";
	std::cin >> number_of_doctors;

	std::cout << "Enter the department type(neonatal unit/surgery): ";
	std::cin >> department_type;

	if (department_type == "neonatal unit") {
		int  number_of_mothers, number_of_newborns;
		double average;

		std::cout << "Enter the number of mothers: ";
		std::cin >> number_of_mothers;

		std::cout << "Enter the number of newborns: ";
		std::cin >> number_of_newborns;

		std::cout << "Enter the average grade: ";
		std::cin >> average;

		HospitalDepartment* department;
		auto neonatal_unit = new NeonatalUnit(name, number_of_doctors, number_of_mothers, number_of_newborns, average);
		department = neonatal_unit;
		this->service.addDepartment(department);

		std::cout << "New surgery department has been added!\n";
	}

	else if (department_type == "surgery") {
		int number_of_patients;

		std::cout << "Enter the number of patients: ";
		std::cin >> number_of_patients;

		HospitalDepartment* department;
		auto surgery = new Surgery(name, number_of_doctors, number_of_patients);
		department = surgery;
		this->service.addDepartment(department);

		std::cout << "New surgery department has been added!\n";
	}

	else
		std::cout << "Not a valid type of department\n";
}

void UI::display_all_departments()
{
	std::cout << "Departments:\n";
	
	for (auto& department : this->service.getAllDepartments())
		std::cout << department->toString() << "\n";
}

void UI::display_efficient_departments()
{
	std::cout << "Efficient Departments:\n";

	for (auto& department : this->service.getAllEfficientDepartments())
		std::cout << department->toString() << "\n";
}

void UI::save_to_file()
{
	std::string file_name;

	std::cout << "Enter the file name: ";
	std::cin >> file_name;

	this->service.writeToFile(file_name);
	std::cout << "The file has been created!\n";
}

void UI::populate_departments()
{
	HospitalDepartment* department;
	auto surgery1 = new Surgery("Regina Maria", 10, 4);
	department = surgery1;
	this->service.addDepartment(department);

	auto surgery2 = new Surgery("Marie Curie", 20, 64);
	department = surgery2;
	this->service.addDepartment(department);

	auto neonatal_unit1 = new NeonatalUnit("Cantacuzino", 20, 10, 15, 8);
	department = neonatal_unit1;
	this->service.addDepartment(department);

	auto neonatal_unit2 = new NeonatalUnit("Marie Curie", 20, 10, 12, 8.7);
	department = neonatal_unit2;
	this->service.addDepartment(department);
}

void print_menu()
{
	std::cout << "1. Add new department.\n";
	std::cout << "2. Show all departments.\n";
	std::cout << "3. Show all efficient departments.\n";
	std::cout << "4. Save sorted departments to file.\n";
	std::cout << "5. Exit.\n";
}

void UI::run_program()
{
	int command;
	this->populate_departments();

	while (true) {
		print_menu();
		std::cout << "> ";
		std::cin >> command;

		switch (command) {
			case 1:
				this->add_new_department();
				break;

			case 2:
				this->display_all_departments();
				break;

			case 3:
				this->display_efficient_departments();
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
}

UI::~UI()
{
	{}
}
