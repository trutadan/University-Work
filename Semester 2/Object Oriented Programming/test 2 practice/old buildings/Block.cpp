#include "Block.h"

Block::Block(const std::string& _address, const int& _year, const int& _totalApartments, const int& _occupiedApartments)
{
	this->address = _address;
	this->constructionYear = _year;
	this->totalApartments = _totalApartments;
	this->occupiedApartments = _occupiedApartments;
}

bool Block::mustBeRestored()
{
	if (0.80 * this->totalApartments <= this->occupiedApartments && this->constructionYear + 40 < CURRENT_YEAR)
		return true;

	return false;
}

bool Block::canBeDemolished()
{
	if (this->totalApartments * 0.05 > this->occupiedApartments)
		return true;

	return false;
}

std::string Block::toString()
{
	return "Block - address: " + this->address + " | costruction year: " + std::to_string(this->constructionYear) + " | total appartments: " + std::to_string(this->totalApartments) + " | occupied appartments: " + std::to_string(this->occupiedApartments);
}

Block::~Block()
{
	{}
}
