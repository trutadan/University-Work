#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor()
{
    {}
}

TemperatureSensor::TemperatureSensor(const std::string& _producer, std::vector<double> _recordings, const double& _diameter, const double& _length)
{
    this->producer = _producer;
    this->recordings = _recordings;
    this->diameter = _diameter;
    this->length = _length;
}

bool TemperatureSensor::sendAlert()
{
    int alertValues = 0;
    for (auto recording : this->recordings) {
        if (recording < 10 || recording > 35)
            alertValues++;

        if (alertValues >= 2)
            return true;
    }

    return false;
}

double TemperatureSensor::getPrice()
{
    double basePrice = 9;

    if (this->diameter < 3 && this->length < 50)
        basePrice += 8;

    return basePrice;
}

std::string TemperatureSensor::toString()
{
    return "Temperature " + Sensor::toString() + " | diameter - " + std::to_string(this->diameter) + " | length - " + std::to_string(this->length) + " | price - " + std::to_string(this->getPrice());
}

TemperatureSensor::~TemperatureSensor()
{
    {}
}
