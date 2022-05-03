//
// Created by Dan on 4/6/2022.
//

#ifndef PROTEINMANAGER_UI_H
#define PROTEINMANAGER_UI_H


#include "Controller.h"

class UI {
private:
    Controller controller;

public:
    UI(Controller _controller);

    void start_program();

    void show_all_proteins() const;

    void show_sorted_proteins_by_given_sequence(const std::string& sequence) const;

};


#endif //PROTEINMANAGER_UI_H
