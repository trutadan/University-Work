#pragma once
#include "HospitalDepartment.h"

class Surgery : public HospitalDepartment
{
public:
	Surgery();

	Surgery(const std::string&, const int&, const int&);

	bool isEfficient() override;

	std::string toString() override;

	~Surgery();

private:
	int numberOfPatients;
};
