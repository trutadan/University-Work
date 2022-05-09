#include "Device.h"

Device::Device()
{
	this->hasWiFi = false;
}

Device::Device(bool _hasWiFi)
{
	this->hasWiFi = _hasWiFi;
}

void Device::addSensor(Sensor* sensor)
{
	this->sensors.push_back(sensor);
}

std::vector<Sensor*> Device::getAllSensors()
{
	return this->sensors;
}

std::vector<Sensor*> Device::getAlertingSensors()
{
	std::vector<Sensor*> alertingSensors;

	std::copy_if(this->sensors.begin(), this->sensors.end(), std::back_inserter(alertingSensors), [](Sensor* sensor) { return sensor->sendAlert(); });

	return alertingSensors;
}

void Device::writeToFile(const std::string& fileName)
{
	std::ofstream fout(fileName);

	std::vector<Sensor*> sortedSensors = this->sensors;
	std::sort(sortedSensors.begin(), sortedSensors.end(), [](Sensor* sensor1, Sensor* sensor2) {return sensor1->getProducer() < sensor2->getProducer(); });

	fout << "Device price - " + std::to_string(this->getPrice()) + "\n";

	std::string stringWiFi;
	if (this->hasWiFi)
		stringWiFi = "yes";
	else
		stringWiFi = "no";

	fout << "It has WiFi - " + stringWiFi + "\n";

	for (auto& sensor : sortedSensors)
		fout << sensor->toString() << "\n";

	fout.close();
}

double Device::getPrice()
{
	double basePrice = 19;
	if (this->hasWiFi)
		basePrice += 20;

	for (auto& sensor : this->sensors)
		basePrice += sensor->getPrice();

	return basePrice;
}

Device::~Device()
{
	for (auto& sensor : this->sensors)
		delete sensor;
}
