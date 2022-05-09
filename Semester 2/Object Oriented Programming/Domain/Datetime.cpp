#include "Datetime.h"

Datetime::Datetime() 
	: year(0), month(0), day(0), hour(0), minutes(0)
{
}

Datetime::Datetime(int _year, int _month, int _day, int _hour, int _minutes)
	: year(_year), month(_month), day(_day), hour(_hour), minutes(_minutes)
{
}

Datetime::Datetime(const Datetime& copy)
	: year(copy.year), month(copy.month), day(copy.day), hour(copy.hour), minutes(copy.minutes)
{
}

int Datetime::get_year() const
{
	return year;
}

int Datetime::get_month() const
{
	return month;
}

int Datetime::get_day() const
{
	return day;
}

int Datetime::get_hour() const
{
	return hour;
}

int Datetime::get_minutes() const
{
	return minutes;
}

void Datetime::set_year(int new_year)
{
	year = new_year;
}

void Datetime::set_month(int new_month)
{
	month = new_month;
}

void Datetime::set_day(int new_day)
{
	day = new_day;
}

void Datetime::set_hour(int new_hour)
{
	hour = new_hour;
}

void Datetime::set_minutes(int new_minutes)
{
	minutes = new_minutes;
}

std::string Datetime::datetime_to_string() const
{
	std::string hour_format = std::to_string(hour);
	if (hour < 10)
		hour_format.insert(0, "0");

	std::string minutes_format = std::to_string(minutes);
	if (minutes < 10)
		minutes_format.insert(0, "0");

	return std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day)
		+ "|" + hour_format + ":" + minutes_format;
}

std::string Datetime::date_to_string() const
{
	return std::to_string(year) + "/" + std::to_string(month) + "/" + std::to_string(day);
}

std::string Datetime::time_to_string() const
{
	std::string hour_format = std::to_string(hour);
	if (hour < 10)
		hour_format.insert(0, "0");

	std::string minutes_format = std::to_string(minutes);
	if (minutes < 10)
		minutes_format.insert(0, "0");

	return hour_format + ":" + minutes_format;
}

bool Datetime::operator==(const Datetime& other) const
{
	return this->year == other.year && this->month == other.month && this->day == other.day && this->hour == other.hour && this->minutes == other.minutes;
}
