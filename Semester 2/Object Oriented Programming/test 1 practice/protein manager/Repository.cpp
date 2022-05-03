//
// Created by Dan on 4/6/2022.
//

#include <algorithm>
#include "Repository.h"

bool Repository::add_protein_to_repository(const Protein &new_protein) {
    const std::vector<Protein>& proteins_from_repository = this->proteins;

    for(const Protein& protein: proteins_from_repository)
        if (protein.get_sequence() == new_protein.get_sequence())
            return false;

    this->proteins.push_back(new_protein);
    return true;
}

bool Repository::remove_protein_from_repository(const std::string &organism_to_remove, const std::string& name_to_remove) {
    const std::vector<Protein>& proteins_from_repository = this->proteins;

    int index;
    for (index = 0; index < proteins_from_repository.size(); ++index)
        if (proteins_from_repository[index].get_organism() == organism_to_remove && proteins_from_repository[index].get_name() == name_to_remove)
            break;

    if (index == proteins_from_repository.size())
        return false;

    this->proteins.erase(this->proteins.begin() + index);
    return true;
}

const std::vector <Protein> &Repository::get_all_proteins_from_repository() const {
    return this->proteins;
}
