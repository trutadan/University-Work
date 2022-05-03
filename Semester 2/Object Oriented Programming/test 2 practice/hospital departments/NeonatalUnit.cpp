#include "NeonatalUnit.h"

NeonatalUnit::NeonatalUnit()
{
	{}
}

NeonatalUnit::NeonatalUnit(const std::string& name, const int& nrDoctors, const int& nrMothers, const int& nrNewborns, const double& average)
{
	this->hospitalName = name;
	this->numberOfDoctors = nrDoctors;
	this->numberOfMothers = nrMothers;
	this->numberOfNewborns = nrNewborns;
	this->averageGrade = average;
}

bool NeonatalUnit::isEfficient()
{
	return (this->averageGrade > 8.5 && this->numberOfNewborns >= this->numberOfMothers);
}

std::string NeonatalUnit::toString()
{
	std::string neonatalUnitString = "Neonatal Unit: name - " + this->hospitalName + " | number of doctors - " + std::to_string(this->numberOfDoctors) + " | number of mothers - " + std::to_string(this->numberOfMothers) + " | number of newborns - " + std::to_string(this->numberOfNewborns) + " | average grade - " + std::to_string(this->averageGrade);
	return neonatalUnitString.substr(0, neonatalUnitString.size() - 4);
}

NeonatalUnit::~NeonatalUnit()
{
	{}
}
