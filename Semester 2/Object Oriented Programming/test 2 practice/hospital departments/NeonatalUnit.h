#pragma once
#include "HospitalDepartment.h"

class NeonatalUnit : public HospitalDepartment
{
public:
	NeonatalUnit();

	NeonatalUnit(const std::string&, const int&, const int&, const int&, const double&);

	bool isEfficient() override;

	std::string toString() override;

	~NeonatalUnit();

private:
	int numberOfMothers;
	int numberOfNewborns;
	double averageGrade;
};

