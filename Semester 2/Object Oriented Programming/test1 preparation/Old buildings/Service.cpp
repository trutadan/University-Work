#include "Service.h"

Service::Service()
{
}

void Service::addBuilding(Building* building)
{
	this->buildings.push_back(building);
}

std::vector<Building*> Service::getAllBuildings()
{
	return this->buildings;
}

std::vector<Building*> Service::getAllToBeRestored()
{
	std::vector<Building*> auxiliar_building_list;

	for (auto& building : this->buildings)
		if (building->mustBeRestored())
			auxiliar_building_list.push_back(building);

	return auxiliar_building_list;
}

std::vector<Building*> Service::getAllToBeDemolished()
{
	std::vector<Building*> auxiliar_building_list;

	for (auto& building : this->buildings)
		if (building->canBeDemolished())
			auxiliar_building_list.push_back(building);

	return auxiliar_building_list;
}

void Service::writeToFile(std::string file_name, std::vector<Building*> _buildings)
{
	std::ofstream fout(file_name);
	for (auto& building : this->buildings)
		fout << building->toString() << "\n";

}

Service::~Service()
{
	for (auto& building : this->buildings)
		delete building;
}
