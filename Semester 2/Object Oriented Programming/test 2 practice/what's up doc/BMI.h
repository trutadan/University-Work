#pragma once
#include "Measurement.h"

class BMI : public Measurement
{
public:
	BMI();

	BMI(const std::string&, const double&);

	bool isNormalValue() override;

	std::string toString() override;

	~BMI();

private:
	double value;
};

