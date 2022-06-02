#include "Repository.h"

Repository::Repository()
{
	{}
}

void Repository::readFromFile(const std::string& fileName)
{
	std::ifstream fin(fileName);

	Equation equation;
	while (fin >> equation)
		this->equations.push_back(equation);

	fin.close();
}

void Repository::addEquation(Equation newEquation)
{
	int index = 0;
	for (Equation equation : this->equations)
		if (equation.getA() == newEquation.getA() && equation.getB() == newEquation.getB() && equation.getC() == newEquation.getC())
			throw std::exception("Equation already existing!");

	this->equations.push_back(newEquation);
}

std::vector<Equation> Repository::getAllFromRepository()
{
	return this->equations;
}

Repository::~Repository()
{
	{}
}
