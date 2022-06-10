#pragma once
#include <string>

class Datetime
{
public:
	Datetime();
	
	Datetime(int _year, int _month, int _day, int _hour, int _minutes);
	
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
