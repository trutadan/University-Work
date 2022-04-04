#pragma once
#include <string>

class Datetime
{
public:
	Datetime();
	
	Datetime(int year, int month, int day, int hour, int minutes);
	
	Datetime(const Datetime& copy);

	int get_year() const;
	int get_month() const;
	int get_day() const;
	int get_hour() const;
	int get_minutes() const;

	void set_year(int new_year);
	void set_month(int new_month);
	void set_day(int new_day);
	void set_hour(int new_hour);
	void set_minutes(int new_minutes);

	std::string datetime_to_string() const;

	std::string date_to_string() const;

	std::string time_to_string() const;

	bool operator==(const Datetime& other)const;

private:
	int year;
	int month;
	int day;

	int hour;
	int minutes;
};
