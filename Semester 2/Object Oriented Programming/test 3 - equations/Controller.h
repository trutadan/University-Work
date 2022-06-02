#pragma once
#include "Repository.h"

class Controller
{
public:
	Controller();

	void readFromFile(const std::string& fileName);

	void addEquation(double a, double b, double c);

	std::string getSolutionOfEquation(double a, double b, double c);

	std::vector<Equation> getAll();

	~Controller();

private:
	Repository repository;
};

