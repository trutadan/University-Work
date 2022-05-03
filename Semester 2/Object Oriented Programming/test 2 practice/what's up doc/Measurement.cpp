#include "Measurement.h"

Measurement::Measurement()
{
    {}
}

Measurement::Measurement(const std::string& _date)
{
    this->date = _date;
}

std::string Measurement::get_date() const
{
    return this->date;
}

Measurement::~Measurement()
{
    {}
}
