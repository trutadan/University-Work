#include "Person.h"

Person::Person()
{
	{}
}

Person::Person(const std::string& _name)
{
	this->name = _name;
}

void Person::addMeasurement(Measurement* measurement)
{
	this->measurements.push_back(measurement);
}

std::vector<Measurement*> Person::getAllMeasurements()
{
	return this->measurements;
}

std::vector<Measurement*> Person::getMeasurementsByMonth(const int& searched_month)
{
	std::vector<Measurement*> measurements_list;
	int integer_month;

	for (auto& measurement : this->measurements) {
		std::string::size_type pos = measurement->get_date().find_first_of(".");
		std::string month_string = measurement->get_date().substr(pos + 1);
		pos = month_string.find_last_of(".");
		month_string += month_string.substr(0, pos);

		integer_month = std::stoi(month_string);

		if (integer_month == searched_month - 1 || integer_month == searched_month)
			measurements_list.push_back(measurement);
	}

	return measurements_list;
}

bool Person::isHealthy(const int& searched_month)
{
	int integer_month;

	for (auto& measurement : getMeasurementsByMonth(searched_month-1))
		if (!measurement->isNormalValue())
			return false;
	
	for (auto& measurement : getMeasurementsByMonth(searched_month))
		if (!measurement->isNormalValue())
			return false;

	return true;
}

std::vector<Measurement*> Person::getMeasurementsNewerThan(const std::string& date)
{
	std::vector<Measurement*> measurements_newer;

	for (auto& measurement : this->measurements)
		if (measurement->get_date() > date)
			measurements_newer.push_back(measurement);

	return measurements_newer;			
}

void Person::writeToFile(const std::string& date, const std::string& file_name)
{
	std::ofstream fout(file_name);

	for (auto& measurement : getMeasurementsNewerThan(date))
			fout << measurement->toString() << "\n";
}

std::string Person::get_name() const
{
	return this->name;
}

Person::~Person()
{
	for (auto& measurement : this->measurements)
		delete measurement;
}
