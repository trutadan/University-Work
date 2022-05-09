#include "Repository.h"

bool Repository::add_patient_to_repository(const Patient& new_patient)
{
    for (const Patient& patient : this->patients)
        if (patient.get_name() == new_patient.get_name())
            return false;

    this->patients.push_back(new_patient);
    return true;
}

bool Repository::remove_patient_from_repository(const std::string& name)
{
    int index = 0;

    for (const Patient& patient : this->patients) {
        if (patient.get_name() == name)
            break;
        
        index++;
        }

    if (index == this->patients.size() || patients[index].get_isQuarantined())
        return false;

    this->patients.erase(this->patients.begin() + index);
    return true;
}

bool Repository::update_patient_from_repository(const std::string& name, const int& new_age, bool new_isInfected, const std::string& new_room_number, bool new_isQuarantined)
{
    int index = 0;

    for (const Patient& patient : this->patients) {
        if (patient.get_name() == name)
            break;

        index++;
    }

    if (index == this->patients.size())
        return false;

    Patient new_patient{ name, new_age, new_isInfected, new_room_number, new_isQuarantined };
    this->patients[index] = new_patient;
}

const std::vector<Patient>& Repository::get_patients_from_repository() const
{
    return this->patients;
}
