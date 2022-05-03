#pragma once
#include "Building.h"

class House : public Building
{
public:
	House(const std::string&, const int&, bool);

	bool mustBeRestored() override;

	bool canBeDemolished() override;

	std::string toString() override;

	~House();

private:
	bool isHistorical;
};

