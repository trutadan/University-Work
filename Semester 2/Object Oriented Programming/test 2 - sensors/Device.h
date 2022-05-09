#pragma once
#include "HumiditySensor.h"
#include "SmokeSensor.h"
#include "TemperatureSensor.h"
#include <fstream>
#include <algorithm>

class Device
{
public:
	Device();

	Device(bool _hasWiFi);

	void addSensor(Sensor* sensor);

	std::vector<Sensor*> getAllSensors();

	std::vector<Sensor*> getAlertingSensors();

	void writeToFile(const std::string& fileName);

	double getPrice();

	~Device();

private:
	bool hasWiFi;
	std::vector<Sensor*> sensors;
};

