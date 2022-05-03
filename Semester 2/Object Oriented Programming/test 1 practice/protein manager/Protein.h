#include <string>

#ifndef PROTEINMANAGER_PROTEIN_H
#define PROTEINMANAGER_PROTEIN_H


class Protein {
private:
    std::string organism;
    std::string name;
    std::string sequence;

public:
    Protein(std::string  organism, std::string  name, std::string  sequence);

    const std::string& get_organism() const;

    const std::string& get_name() const;

    const std::string& get_sequence() const;

    std::string to_string() const;
};


#endif //PROTEINMANAGER_PROTEIN_H
