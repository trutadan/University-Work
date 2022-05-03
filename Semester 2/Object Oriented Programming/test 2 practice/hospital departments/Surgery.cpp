#include "Surgery.h"

Surgery::Surgery()
{
    {}
}

Surgery::Surgery(const std::string& name, const int& nrDoctors, const int& nrPatients)
{
    this->hospitalName = name;
    this->numberOfDoctors = nrDoctors;
    this->numberOfPatients = nrPatients;
}

bool Surgery::isEfficient()
{
    return (this->numberOfPatients / numberOfDoctors >= 2);
}

std::string Surgery::toString()
{
    return "Surgery: name - " + this->hospitalName + " | number of doctors - " + std::to_string(this->numberOfDoctors) + " | number of patients - " + std::to_string(this->numberOfPatients);
}

Surgery::~Surgery()
{
    {}
}
