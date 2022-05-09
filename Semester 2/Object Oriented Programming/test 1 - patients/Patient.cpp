#include "Patient.h"

Patient::Patient(const std::string& _name, const int& _age, const bool& _isInfected, const std::string& _room_number, const bool& _isQuarantined) : name(_name), age(_age), isInfected(_isInfected), room_number(_room_number), isQuarantined(_isQuarantined)
{
}

const std::string& Patient::get_name() const
{
	return this->name;
}

const int& Patient::get_age() const
{
	return this->age;
}

const bool& Patient::get_isInfected() const
{
	return this->isInfected;
}

const std::string& Patient::get_room_number() const
{
	return this->room_number;
}

const bool& Patient::get_isQuarantined() const
{
	return this->isQuarantined;
}

void Patient::set_isQuarantined(const bool& new_value)
{
	this->isQuarantined = new_value;
}

void Patient::set_room_number(const std::string& new_value)
{
	this->room_number = new_value;
}

std::string Patient::to_string() const
{
	std::string patient_string;

	std::string isInfected_string;
	if (isInfected)
		isInfected_string = "true";
	else isInfected_string = "false";

	std::string isQuarantined_string;
	if (isQuarantined)
		isQuarantined_string = "true";
	else isQuarantined_string = "false";

	patient_string = this->name + " | " + std::to_string(this->age) + " | " + isInfected_string + " | " + this->room_number + " | " + isQuarantined_string;

	return patient_string;
}
