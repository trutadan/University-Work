#pragma once
#include <string>
#include <istream>
#include <sstream>

class Equation
{
public:
	Equation();

	Equation(double _a, double _b, double _c);

	double getA();

	double getB();

	double getC();

	std::string toString();

	friend std::istream& operator>>(std::istream& reader, Equation& equation);

	bool isReal();

	~Equation();

private:
	double a;
	double b;
	double c;

};

