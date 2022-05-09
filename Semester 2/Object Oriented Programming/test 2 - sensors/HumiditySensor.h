#pragma once
#include "Sensor.h"

class HumiditySensor : public Sensor
{
public:
	HumiditySensor();

	HumiditySensor(const std::string& _producer, std::vector<double> recordings);

	bool sendAlert() override;

	double getPrice() override;

	std::string toString() override;

	~HumiditySensor();
};

