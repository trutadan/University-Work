//
// Created by Dan on 4/6/2022.
//

#include "Protein.h"

#include <utility>

const std::string &Protein::get_organism() const {
    return this->organism;
}

const std::string &Protein::get_name() const {
    return this->name;
}

const std::string &Protein::get_sequence() const {
    return this->sequence;
}

std::string Protein::to_string() const {
    std::string protein_string;
    protein_string = this->organism + " | " + this->name + " | " + this->sequence;

    return protein_string;
}

Protein::Protein(std::string _organism, std::string _name, std::string _sequence) : organism(std::move(_organism)), name(std::move(_name)), sequence(std::move(_sequence)) {

}
