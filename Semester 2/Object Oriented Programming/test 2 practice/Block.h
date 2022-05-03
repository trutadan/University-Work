#pragma once
#include "Building.h"

class Block : public Building
{
public:
	Block(const std::string&, const int&, const int&, const int&);

	bool mustBeRestored() override;

	bool canBeDemolished() override;

	std::string toString() override;

	~Block();

private:
	int totalApartments;
	int occupiedApartments;
};

