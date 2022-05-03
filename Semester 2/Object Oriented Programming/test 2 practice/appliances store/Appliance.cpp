#include "Appliance.h"

Appliance::Appliance()
{
	{}
}

Appliance::Appliance(const std::string& _id, const double& _weight)
{
	this->id = _id;
	this->weight = _weight;
}

std::string Appliance::get_id() const
{
	return this->id;
}

Appliance::~Appliance()
{
	{}
}
