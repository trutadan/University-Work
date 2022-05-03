#pragma once
#include <string>

class Task
{
private:
	std::string description;
	int duration;
	int priority;

public:
	Task(const std::string& description, const int& duration, const int& priority);

	const std::string& get_description() const;

	const int& get_duration() const;

	const int& get_priority() const;

	std::string to_string() const;
};

