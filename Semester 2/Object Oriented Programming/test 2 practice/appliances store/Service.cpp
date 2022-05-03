#include "Service.h"
#include <iostream>

Service::Service()
{
    this->filterElectricity = 0;
}

void Service::addAppliance(Appliance* appliance)
{
    this->appliances.push_back(appliance);
}

std::vector<Appliance*> Service::getAllAppliances()
{
    return this->appliances;
}

std::vector<Appliance*> Service::getAllWithConsumedElectricityLessThan(const double& maxElectricity)
{
    std::vector<Appliance*> filtered_appliances;
    
    std::copy_if(this->appliances.begin(), this->appliances.end(), std::back_inserter(filtered_appliances), [&maxElectricity](Appliance* appliance) { return appliance->consumedElectricity() < maxElectricity; });
    
    return filtered_appliances;
}

void Service::writeToFile(const std::string& file_name)
{
    std::ofstream fout(file_name);

    std::vector<Appliance*> filtered_appliances;
    std::copy_if(this->appliances.begin(), this->appliances.end(), std::back_inserter(filtered_appliances), [this](Appliance* appliance) { return appliance->consumedElectricity() > this->get_filterElectricity(); });
    std::sort(filtered_appliances.begin(), filtered_appliances.end(), [](Appliance* appliance1, Appliance* appliance2) { return appliance1->get_id() < appliance2->get_id(); });

    for (auto& appliance : filtered_appliances)
        fout << appliance->toString() << "\n";
}

const double& Service::get_filterElectricity() const
{
    return this->filterElectricity;
}

void Service::set_filterElectricity(double _filterElectricity)
{
    this->filterElectricity = _filterElectricity;
}

Service::~Service()
{
    {}
}
