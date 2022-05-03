#include "BP.h"

BP::BP()
{
    {}
}

BP::BP(const std::string& _date, const int& diastolic, const int& systolic)
{
    this->date = _date;
    this->diastolicValue = diastolic;
    this->systolicValue = systolic;
}

bool BP::isNormalValue()
{
    if (this->systolicValue >= 90 && this->systolicValue <= 119 && this->diastolicValue >= 60 && this->diastolicValue <= 79)
        return true;

    return false;
}

std::string BP::toString()
{
    return "BP: date - " + this->date + " | systolic value - " + std::to_string(this->systolicValue) + " | diastolic value - " + std::to_string(this->diastolicValue);
}

BP::~BP()
{
    {}
}
