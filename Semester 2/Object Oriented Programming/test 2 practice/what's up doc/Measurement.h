#pragma once
#include <string>

class Measurement
{
public:
	Measurement();

	Measurement(const std::string&);

	virtual bool isNormalValue() = 0;

	virtual std::string toString() = 0;

	std::string get_date() const;

	~Measurement();

protected:
	std::string date;
};

