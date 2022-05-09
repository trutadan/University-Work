#include "Sensor.h"

Sensor::Sensor()
{
	{}
}

Sensor::Sensor(const std::string& _producer, std::vector<double> _recordings)
{
	this->producer = _producer;
	this->recordings = _recordings;
}

std::string Sensor::toString()
{
	std::string sensor = "Sensor: producer - " + this->producer + " | recordings - ";
	for (auto recording : this->recordings)
		sensor += std::to_string(recording) + " ";

	return sensor;
}

std::string Sensor::getProducer()
{
	return this->producer;
}

Sensor::~Sensor()
{
	{}
}
