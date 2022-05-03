#include "DishWasher.h"

DishWasher::DishWasher()
{
	{}
}

DishWasher::DishWasher(const std::string& _id, const double& _weight, const double& _washing, const double& _consumed)
{
	this->id = _id;
	this->weight = _weight;
	this->washingCycleLength = _washing;
	this->consumedElectricityForOneHour = _consumed;
}

double DishWasher::consumedElectricity()
{
	return this->washingCycleLength * this->consumedElectricityForOneHour * 20;
}

std::string DishWasher::toString()
{
	return "DishWasher: id - " + this->id + " | weight - " + std::to_string(this->weight) + " | washing cycle length - " + std::to_string(this->washingCycleLength) + " | consumed electricity for one hour - " + std::to_string(this->consumedElectricityForOneHour);
}

DishWasher::~DishWasher()
{
	{}
}
