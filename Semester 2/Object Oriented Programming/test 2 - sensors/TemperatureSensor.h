#pragma once
#include "Sensor.h"
class TemperatureSensor : public Sensor
{
public:
	TemperatureSensor();

	TemperatureSensor(const std::string& _producer, std::vector<double> recordings, const double& diameter, const double& length);

	bool sendAlert() override;

	double getPrice() override;

	std::string toString() override;

	~TemperatureSensor();

private:
	double diameter;
	double length;
};

