#pragma once
#include "NeonatalUnit.h"
#include "Surgery.h"
#include <vector>
#include <fstream>
#include <algorithm>

class Service
{
public:
	Service();

	void addDepartment(HospitalDepartment* department);

	std::vector<HospitalDepartment*> getAllDepartments();

	std::vector<HospitalDepartment*> getAllEfficientDepartments();

	void writeToFile(const std::string&);

	~Service();

private:
	std::vector<HospitalDepartment*> departments;
};

