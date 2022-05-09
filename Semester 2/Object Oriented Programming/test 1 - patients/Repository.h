#pragma once
#include <vector>
#include "Patient.h"
class Repository
{
private:
	std::vector<Patient> patients;

public:
	bool add_patient_to_repository(const Patient& new_patient);

	bool remove_patient_from_repository(const std::string& name);

	bool update_patient_from_repository(const std::string& name, const int& new_age, bool new_isInfected, const std::string& new_room_number, bool new_isQuarantined);

	const std::vector<Patient>& get_patients_from_repository() const;
};

