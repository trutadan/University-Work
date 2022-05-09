#pragma once
#include "Sensor.h"

class SmokeSensor : public Sensor
{
public:
	SmokeSensor();

	SmokeSensor(const std::string& _producer, std::vector<double> _recordings);

	bool sendAlert() override;

	double getPrice() override;

	std::string toString() override;

	~SmokeSensor();

};

