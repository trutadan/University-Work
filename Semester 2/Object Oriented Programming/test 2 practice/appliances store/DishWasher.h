#pragma once
#include "Appliance.h"

class DishWasher : public Appliance
{
public:
	DishWasher();

	DishWasher(const std::string&, const double&, const double&, const double&);

	double consumedElectricity() override;

	std::string toString() override;

	~DishWasher();

private:
	double washingCycleLength;
	double consumedElectricityForOneHour;
};

