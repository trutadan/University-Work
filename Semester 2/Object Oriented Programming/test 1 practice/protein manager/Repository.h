//
// Created by Dan on 4/6/2022.
//
#include "Protein.h"
#include <vector>

#ifndef PROTEINMANAGER_REPOSITORY_H
#define PROTEINMANAGER_REPOSITORY_H


class Repository {
private:
    std::vector<Protein> proteins;

public:
    bool add_protein_to_repository(const Protein& new_protein);

    bool remove_protein_from_repository(const std::string& organism_to_remove, const std::string& name_to_remove);

    const std::vector<Protein>& get_all_proteins_from_repository() const;
};


#endif //PROTEINMANAGER_REPOSITORY_H
