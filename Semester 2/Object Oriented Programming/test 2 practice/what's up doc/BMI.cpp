#include "BMI.h"

BMI::BMI()
{
	{}
}

BMI::BMI(const std::string& _date, const double& _value)
{
	this->date = _date;
	this->value = _value;
}

bool BMI::isNormalValue()
{
	if (this->value >= 18.5 && this->value <= 25)
		return true;

	return false;
}

std::string BMI::toString()
{
	return "BMI: date - " + this->date + " | value - " + std::to_string(this->value);
}

BMI::~BMI()
{
	{}
}
