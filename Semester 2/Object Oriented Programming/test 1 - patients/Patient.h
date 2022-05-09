#pragma once
#include <string>
class Patient
{
private:
	std::string name;
	int age;
	bool isInfected;
	std::string room_number;
	bool isQuarantined;

public:
	Patient(const std::string& _name, const int& _age, const bool& _isInfected, const std::string& _room_number, const bool& _isQuarantined);

	const std::string& get_name() const;

	const int& get_age() const;

	const bool& get_isInfected() const;

	const std::string& get_room_number() const;

	const bool& get_isQuarantined() const;

	void set_isQuarantined(const bool& new_value);

	void set_room_number(const std::string& new_value);

	std::string to_string() const;
};

