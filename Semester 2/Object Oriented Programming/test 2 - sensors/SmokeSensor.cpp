#include "SmokeSensor.h"

SmokeSensor::SmokeSensor()
{
	{}
}

SmokeSensor::SmokeSensor(const std::string& _producer, std::vector<double> _recordings)
{
	this->producer = _producer;
	this->recordings = _recordings;
}

bool SmokeSensor::sendAlert()
{
	for (auto recording: this->recordings)
		if (recording > 1600)
			return true;

	return false;
}

double SmokeSensor::getPrice()
{
	return 25;
}

std::string SmokeSensor::toString()
{
	return "Smoke " + Sensor::toString() + " | price - " + std::to_string(this->getPrice());
}

SmokeSensor::~SmokeSensor()
{
	{}
}
