#include "HumiditySensor.h"

HumiditySensor::HumiditySensor()
{
    {}
}

HumiditySensor::HumiditySensor(const std::string& _producer, std::vector<double> _recordings)
{
    this->producer = _producer;
    this->recordings = _recordings;
}

bool HumiditySensor::sendAlert()
{
    int alertValues = 0;
    for (auto recording : this->recordings){
        if (recording < 30 || recording > 85)
            alertValues++;
        
        if (alertValues >= 2)
            return true;
    }

    return false;
}

double HumiditySensor::getPrice()
{
    return 4;
}

std::string HumiditySensor::toString()
{
    return "Humidity " + Sensor::toString() + " | price - " + std::to_string(this->getPrice());
}

HumiditySensor::~HumiditySensor()
{
    {}
}
