#pragma once
#include "BMI.h"
#include "BP.h"
#include <vector>
#include <fstream>

class Person
{
public:
	Person();

	Person(const std::string&);

	void addMeasurement(Measurement* measurement);

	std::vector<Measurement*> getAllMeasurements();

	std::vector<Measurement*> getMeasurementsByMonth(const int&);

	bool isHealthy(const int&);

	std::vector<Measurement*> getMeasurementsNewerThan(const std::string&);

	void writeToFile(const std::string&, const std::string&);

	std::string get_name() const;

	~Person();

private:
	std::string name;
	std::vector<Measurement*> measurements;
};

