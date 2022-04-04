#pragma once
#include "Datetime.h"
#include <Windows.h>

class Event
{
public:
	Event();
	
	Event(std::string, std::string, Datetime, int, std::string);
	
	Event(const Event& copy);

	std::string get_title() const;
	std::string get_description() const;
	Datetime get_datetime() const;
	int get_number_of_people() const;
	std::string get_link() const;

	void set_description(std::string new_description);
	void set_datetime(Datetime new_datetime);
	void set_number_of_people(int new_number_of_people);
	void set_link(std::string new_link);

	bool operator==(const Event& other)const;

	friend std::istream& operator>>(std::istream& reader, Event& event);

	void open() const;

private:
	std::string title;
	std::string description;
	Datetime datetime;
	int number_of_people;
	std::string link;
};