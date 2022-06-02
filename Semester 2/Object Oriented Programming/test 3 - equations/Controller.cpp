#include "Controller.h"

Controller::Controller()
{
	{}
}

void Controller::readFromFile(const std::string& fileName)
{
	this->repository.readFromFile(fileName);
}

void Controller::addEquation(double a, double b, double c)
{
	if (a == 0)
		throw std::exception("a can't be 0!");

	Equation equation(a, b, c);
	this->repository.addEquation(equation);
}

std::string Controller::getSolutionOfEquation(double a, double b, double c)
{
	double delta = b * b - 4 * a * c;
	double x1, x2;
	std::string solutions;

	if (delta < 0) {
		delta *= -1;
		x1 = -b / (2 * a);
		solutions += "x1 = " + std::to_string(x1) + "i * " + std::to_string(sqrt(delta) / (2 * a));
		solutions += "; x2 = " + std::to_string(x1) + "-i * " + std::to_string(sqrt(delta) / (2 * a));
	}

	if (delta == 0) {
		solutions += "x1 = x2 = " + std::to_string((-b)/(2*a));
	}

	else {
		x1 = (-b + sqrt(delta)) / (2 * a);
		x2 = (-b - sqrt(delta)) / (2 * a);
		solutions += "x1 = " + std::to_string(x1);
		solutions += "; x2 = " + std::to_string(x2);
	}

	return solutions;
}

std::vector<Equation> Controller::getAll()
{
	return this->repository.getAllFromRepository();
}

Controller::~Controller()
{
	{}
}
