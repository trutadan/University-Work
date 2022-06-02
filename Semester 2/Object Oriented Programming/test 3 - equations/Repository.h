#pragma once
#include "Equation.h"
#include <vector>
#include <fstream>
class Repository
{
public:
	Repository();

	void readFromFile(const std::string& fileName);

	void addEquation(Equation newEquation);

	std::vector<Equation> getAllFromRepository();

	~Repository();

private:
	std::vector<Equation> equations;
};

