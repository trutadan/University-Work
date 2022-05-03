//
// Created by Dan on 4/6/2022.
//

#ifndef PROTEINMANAGER_CONTROLLER_H
#define PROTEINMANAGER_CONTROLLER_H


#include "Repository.h"

class Controller {
private:
    Repository repository;

public:
    explicit Controller(Repository  _repository);

    bool add_protein(const Protein& new_protein);

    bool remove_protein(const std::string& organism, const std::string& name_to_remove);

    const std::vector<Protein>& get_all_proteins() const;

    std::vector<Protein> get_all_proteins_sorted_for_given_sequence(const std::string& sequence) const;
};


#endif //PROTEINMANAGER_CONTROLLER_H
