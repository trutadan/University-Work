#include "House.h"

House::House(const std::string& _address, const int& _year, bool _isHistorical)
{
	this->address = _address;
	this->constructionYear = _year;
	this->isHistorical = _isHistorical;
}

bool House::mustBeRestored()
{
	if (this->constructionYear + 100 < CURRENT_YEAR)
		return true;

	return false;
}

bool House::canBeDemolished()
{
	if (!this->isHistorical)
		return true;

	return false;
}

std::string House::toString()
{
	std::string house_string = "House - address: " + this->address + " | costruction year: " + std::to_string(this->constructionYear) + " | is historical: ";
	if (this->isHistorical)
		house_string += "true";
	else
		house_string += "false";

	return house_string;
}

House::~House()
{
	{}
}
