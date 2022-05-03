#include "Refrigerator.h"

Refrigerator::Refrigerator()
{
	{}
}

Refrigerator::Refrigerator(const std::string& _id, const double& _weight, const std::string& _electricityUsageClass, bool _hasFreezer)
{
	this->id = _id;
	this->weight = _weight;
	this->electricityUsageClass = _electricityUsageClass;
	this->hasFreezer = _hasFreezer;
}

double Refrigerator::consumedElectricity()
{
	double consumed=0;
	
	if (this->hasFreezer)
		consumed += 20;
	
	double x=0;
	if (this->electricityUsageClass == "A")
		x = 3;

	else if (this->electricityUsageClass == "A+")
		x = 2.5;

	else if (this->electricityUsageClass == "A++")
		x = 2;

	consumed += x * 30;

	return consumed;
}

std::string Refrigerator::toString()
{
	std::string refrigerator_string = "Refrigerator: id - " + this->id + " | weight - " + std::to_string(this->weight) + " | electricity usage class - " + this->electricityUsageClass + " | has freezer - ";
	
	if (this->hasFreezer)
		refrigerator_string += "true";

	else
		refrigerator_string += "false";

	return refrigerator_string;
}

Refrigerator::~Refrigerator()
{
	{}
}
