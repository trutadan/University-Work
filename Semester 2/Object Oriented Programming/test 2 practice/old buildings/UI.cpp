#include "UI.h"
#include <iostream>

UI::UI(Service _service)
{
	this->service = _service;
}

void UI::add_new_building()
{
	std::string type;

	std::cout << "What type of building: house/block?\n> ";
	std::cin >> type;

	if (type == "house") {
		int year;
		std::string address, historical;

		std::cout << "> year = ";
		std::cin >> year;

		std::cout << "> address = ";
		std::cin >> address;

		std::cout << "> is historical: yes/no = ";
		std::cin >> historical;

		bool isHistorical;

		if (historical == "yes")
			isHistorical = true;

		else if (historical == "no")
			isHistorical = false;

		else {
			std::cout << "Not a valid input provided";
			return;
		}

		Building* building;
		auto house = new House(address, year, isHistorical);
		building = house;

		this->service.addBuilding(building);
	}

	else if (type == "block") {
		int year, total, occupied;
		std::string address;

		std::cout << "> year = ";
		std::cin >> year;

		std::cout << "> address = ";
		std::cin >> address;

		std::cout << "> total appartments = ";
		std::cin >> total;
		
		std::cout << "> occupied appartments = ";
		std::cin >> occupied;

		Building* building;
		auto block = new Block(address, year, total, occupied);
		building = block;

		this->service.addBuilding(building);
	}

	else
		std::cout << "Not a valid type provided!";
}

void UI::display_all_buildings()
{
	std::cout << "Buildings:\n";
	for (auto& building : this->service.getAllBuildings())
		std::cout << building->toString() << std::endl;
}

void UI::display_restored_buildings()
{
	int year;
	std::cout << "year = ";
	std::cin >> year;

	std::cout << "Restored buildings:\n";
	for (auto& building : this->service.getAllToBeRestored())
		if (building->get_constructionYear() > year)
			std::cout << building->toString() << std::endl;
}

void UI::save_to_file()
{
	std::string restored_buildings_file, demolished_buildings_file;
	
	std::cout << "Restored buildings file: ";
	std::cin >> restored_buildings_file;

	std::cout << "Demolished buildings file: ";
	std::cin >> demolished_buildings_file;

	this->service.writeToFile(restored_buildings_file, this->service.getAllToBeRestored());

	this->service.writeToFile(demolished_buildings_file, this->service.getAllToBeDemolished());
}

void UI::populate_buildings()
{
	Building* building;
	auto block = new Block("Turda", 1934, 100, 99);
	building = block;
	this->service.addBuilding(building);

	block = new Block("Tiganime", 1971, 300, 190 );
	building = block;
	this->service.addBuilding(building);

	auto house = new House("Zlatna", 1919, false);
	building = house;
	this->service.addBuilding(house);
}

void print_menu()
{
	std::cout << "1. Add new building.\n";
	std::cout << "2. Show all buildings.\n";
	std::cout << "3. Show restored buildings.\n";
	std::cout << "4. Save to file.\n";
	std::cout << "5. Exit.\n";
}

void UI::run_program()
{
	int command;
	this->populate_buildings();

	while (true) {
		print_menu();

		std::cout << "> ";
		std::cin >> command;
		
		switch (command) {

		case 1:
			this->add_new_building();
			break;

		case 2:
			this->display_all_buildings();
			break;

		case 3:
			this->display_restored_buildings();
			break;

		case 4:
			this->save_to_file();
			break;

		case 5:
			return;

		default:
			std::cout << "Not a valid command!\n";
		}

	}
}

UI::~UI()
{
	{}
}
