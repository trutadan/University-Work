#pragma once
#include "Building.h"
#include "Block.h"
#include "House.h"
#include <vector>
#include <fstream>

class Service
{
public:
	Service();

	void addBuilding(Building*);

	std::vector<Building*> getAllBuildings();

	std::vector<Building*> getAllToBeRestored();

	std::vector<Building*> getAllToBeDemolished();

	void writeToFile(std::string, std::vector<Building*>);

	~Service();

private:
	std::vector<Building*> buildings;
};

