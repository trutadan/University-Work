#pragma once
#include <vector>
#include <fstream>
#include <algorithm>
#include "DishWasher.h"
#include "Refrigerator.h"

class Service
{
public:
	Service();

	void addAppliance(Appliance* appliance);

	std::vector<Appliance*> getAllAppliances();

	std::vector<Appliance*> getAllWithConsumedElectricityLessThan(const double&);

	void writeToFile(const std::string&);

	const double& get_filterElectricity() const;

	void set_filterElectricity(double);

	~Service();

private:
	std::vector<Appliance*> appliances;
	double filterElectricity;
};

