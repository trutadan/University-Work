#include "Building.h"

Building::Building()
{
	{}
}

Building::Building(const std::string& _address, const int& _year)
{
	this->address = _address;
	this->constructionYear = _year;
}

int Building::get_constructionYear() const
{
	return this->constructionYear;
}

Building::~Building()
{
	{}
}
