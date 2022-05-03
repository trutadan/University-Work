#pragma once
#include <string>

class Appliance
{
public:
	Appliance();

	Appliance(const std::string&, const double&);

	virtual double consumedElectricity() = 0;

	virtual std::string toString() = 0;

	std::string get_id() const;

	~Appliance();

protected:
	std::string id;
	double weight;
};

