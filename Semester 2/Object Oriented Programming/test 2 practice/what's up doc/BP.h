#pragma once
#include "Measurement.h"

class BP : public Measurement
{
public:
	BP();

	BP(const std::string&, const int&, const int&);

	bool isNormalValue() override;

	std::string toString() override;

	~BP();

private:
	int systolicValue;
	int diastolicValue;
};

