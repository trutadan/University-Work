#include "HospitalDepartment.h"

HospitalDepartment::HospitalDepartment()
{
	{}
}

HospitalDepartment::HospitalDepartment(const std::string& _name, const int& _nrOfDoctors)
{
	this->hospitalName = _name;
	this->numberOfDoctors = _nrOfDoctors;
}

std::string HospitalDepartment::get_name()
{
	return this->hospitalName;
}

HospitalDepartment::~HospitalDepartment()
{
	{}
}
