#include "Controller.h"

bool Controller::add_patient(const std::string& _name, const int& _age, const bool& _isInfected, const std::string& _room_number, const bool& _isQuarantined)
{
    Patient new_patient{ _name, _age, _isInfected, _room_number, _isQuarantined };

    return this->repository.add_patient_to_repository(new_patient);
}

bool Controller::remove_patient(const std::string& name)
{
    /*
    Remove patient if there exists one with the given name.
    Return: true if the patient has been removed, false otherwise.
    */

    return this->repository.remove_patient_from_repository(name);
}

const std::vector<Patient>& Controller::get_all_patients() const
{
    return this->repository.get_patients_from_repository();
}

void Controller::quarantine_all()
{
    /*
    Quarantine all persons that are infected or that are in the same room with an infected person.
    */

    std::vector<std::string> rooms;

    for (const Patient& patient : this->repository.get_patients_from_repository())
        if (patient.get_isInfected())
            if (std::find(rooms.begin(), rooms.end(), patient.get_room_number()) == rooms.end())
                rooms.push_back(patient.get_room_number());

    int patients_size = this->get_all_patients().size();
    for (const std::string& room : rooms) {

        for (Patient patient : this->get_all_patients()) {
            if (patient.get_room_number() == room) {
                Patient new_patient = patient;
                new_patient.set_room_number("Q" + new_patient.get_room_number());
                new_patient.set_isQuarantined(true);

                this->repository.update_patient_from_repository(new_patient.get_name(), new_patient.get_age(), new_patient.get_isInfected(), new_patient.get_room_number(), new_patient.get_isQuarantined());
            }

        }

    }
}
