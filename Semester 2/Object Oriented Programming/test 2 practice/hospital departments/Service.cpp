#include "Service.h"

Service::Service()
{
    {}
}


void Service::addDepartment(HospitalDepartment* department)
{
    this->departments.push_back(department);
}

std::vector<HospitalDepartment*> Service::getAllDepartments()
{
    return this->departments;
}

std::vector<HospitalDepartment*> Service::getAllEfficientDepartments()
{
    std::vector<HospitalDepartment*> efficient_departments;

    for (auto& department : this->departments)
        if (department->isEfficient())
            efficient_departments.push_back(department);

    return efficient_departments;
}

void Service::writeToFile(const std::string& file_name)
{
    std::ofstream fout(file_name);

    std::vector<HospitalDepartment*> sorted_departments = this->departments;

    auto sort_method = [](HospitalDepartment* department1, HospitalDepartment* department2) {
        return department1->get_name() < department2->get_name();
    };

    std::sort(sorted_departments.begin(), sorted_departments.end(), sort_method);

    for (auto& department : sorted_departments) {
        std::string efficency;

        if (department->isEfficient())
            efficency = " | is efficient";

        else 
            efficency = " | is not efficient";
        
        fout << department->toString() << efficency << '\n';
    }
}

Service::~Service()
{
    {}
}
