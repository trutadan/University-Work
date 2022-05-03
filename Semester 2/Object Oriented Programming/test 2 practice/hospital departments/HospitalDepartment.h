#pragma once
#include <string>
class HospitalDepartment
{
public:
	HospitalDepartment();

	HospitalDepartment(const std::string&, const int&);

	virtual bool isEfficient() = 0;

	virtual std::string toString() = 0;

	std::string get_name();

	~HospitalDepartment();

protected:
	std::string hospitalName;
	int numberOfDoctors;
};

