#pragma once
#include "Repository.h"
class Controller
{
private:
	Repository repository;

public:
	Controller(const Repository& _r) : repository(_r) {};

	bool add_patient(const std::string& _name, const int& _age, const bool& _isInfected, const std::string& _room_number, const bool& _isQuarantined);

	bool remove_patient(const std::string& name);

	const std::vector<Patient>& get_all_patients() const;

	void quarantine_all();
};

