#include "Equation.h"

Equation::Equation()
{
	{}
}

Equation::Equation(double _a, double _b, double _c)
{
	this->a = _a;
	this->b = _b;
	this->c = _c;
}

double Equation::getA()
{
	return this->a;
}

double Equation::getB()
{
	return this->b;
}

double Equation::getC()
{
	return this->c;
}

std::string Equation::toString()
{
	std::string equationString;
	if (a < 0)
		equationString += std::to_string(a) + "*x^2";

	else if (a > 0)
		equationString += std::to_string(a) + "*x^2";

	if (b < 0)
		equationString += std::to_string(b) + "*x";

	else if (b > 0)
		equationString += "+" + std::to_string(b) + "*x";

	if (c < 0)
		equationString += std::to_string(c);

	else if (c > 0)
		equationString += "+" + std::to_string(c);

	return equationString;
}

bool Equation::isReal()
{
	double delta = b * b - 4 * a * c;
	if (delta < 0)
		return false;

	return true;
}

Equation::~Equation()
{
	{}
}

std::istream& operator>>(std::istream& reader, Equation& equation)
{
	std::string line;
	std::getline(reader, line);
	if (line.empty())
		return reader;

	std::stringstream stream(line);

	std::string aString, bString, cString;
	double a, b, c;

	std::getline(stream, aString, ',');
	std::getline(stream, bString, ',');
	std::getline(stream, cString, ',');

	a = std::stod(aString);
	b = std::stod(bString);
	c = std::stod(cString);

	equation = Equation(a, b, c);
	return reader;
}
