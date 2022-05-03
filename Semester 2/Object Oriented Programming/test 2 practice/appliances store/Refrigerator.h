#pragma once
#include "Appliance.h"

class Refrigerator : public Appliance
{
public:
	Refrigerator();
	
	Refrigerator(const std::string&, const double&, const std::string&, bool);

	double consumedElectricity() override;

	std::string toString() override;

	~Refrigerator();

private:
	std::string electricityUsageClass;
	bool hasFreezer;
};

