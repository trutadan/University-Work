//
// Created by Dan on 4/6/2022.
//

#include "Controller.h"

#include <utility>
#include <algorithm>

bool Controller::add_protein(const Protein &new_protein) {
    return this->repository.add_protein_to_repository(new_protein);
}

bool Controller::remove_protein(const std::string &organism, const std::string& name_to_remove) {
    /*
     Remove a protein from the repository.
     Return: true if the protein has been removed, false if the searched protein does not exist.
     */

    return this->repository.remove_protein_from_repository(organism, name_to_remove);
}

const std::vector<Protein> &Controller::get_all_proteins() const {
    return this->repository.get_all_proteins_from_repository();
}

std::vector<Protein> Controller::get_all_proteins_sorted_for_given_sequence(const std::string &sequence) const {
    /*
     Sort the list of proteins by the name and then create a new list which contains only the proteins that match the given sequence.
     Return: the sorted list.
     */

    std::vector<Protein> sorted_proteins;

    auto sorting_method = [](const Protein& first_protein, const Protein& second_protein){
        return first_protein.get_name() < second_protein.get_name();
    };

    std::vector<Protein> proteins_from_repository = this->repository.get_all_proteins_from_repository();
    std::sort(proteins_from_repository.begin(), proteins_from_repository.end(), sorting_method);

    for(const Protein& protein: proteins_from_repository)
        if(protein.get_sequence().find(sequence) != std::string::npos)
            sorted_proteins.push_back(protein);

    return sorted_proteins;
}

Controller::Controller(Repository _repository) : repository(std::move(_repository))
{

}
