//
// Created by Dan on 4/6/2022.
//

#include <iostream>
#include <sstream>
#include <utility>
#include "UI.h"



std::vector<std::string> split_command(const std::string& command, char separator){
    std::vector<std::string> arguments;
    std::string argument;
    std::istringstream argumentStream(command);

    bool single_argument = true;
    while (std::getline(argumentStream, argument, separator)) {
        arguments.push_back(argument);
        single_argument = false;
    }

    if (single_argument)
        arguments.push_back(command);

    return arguments;
}

void print_menu(){
    std::cout<<"\n> remove,<organism>,<name>\n";
    std::cout<<"> show all\n";
    std::cout<<"> display sorted,<sequence>\n";
    std::cout<<"> exit\n";
}

void UI::start_program() {
    std::string command;
    std::vector<std::string> arguments;

    std::cout<<"Welcome to protein manager!\n";

    while(true){
        print_menu();
        std::cout << "> ";

        std::getline(std::cin, command);
        arguments = split_command(command, ',');

        if (arguments.size() == 1 && arguments[0] == "show all"){
            this->show_all_proteins();
        }

        else if (arguments.size() == 1 && arguments[0] == "exit")
            break;

        else if(arguments.size() == 3 && arguments[0] == "remove"){
            bool removal_status;
            removal_status = this->controller.remove_protein(arguments[1], arguments[2]);

            if (removal_status)
                std::cout<<"The protein has been successfully removed!\n";

            else
                std::cout<<"The protein hasn't been removed!\n";
        }

        else if(arguments.size() == 2 && arguments[0] == "display sorted"){
            this->show_sorted_proteins_by_given_sequence(arguments[1]);
        }

        else
            std::cout<<"Unknown command!\n";
    }

    std::cout<<"Thank you for using our application!\n";
}

void UI::show_all_proteins() const {
    std::vector<Protein> proteins = this->controller.get_all_proteins();

    if (proteins.empty()){
        std::cout<<"There are no proteins in the repository! Add some.\n";
        return;
    }

    for(const Protein& protein: proteins)
        std::cout<<protein.to_string()<<"\n";
}

void UI::show_sorted_proteins_by_given_sequence(const std::string& sequence) const {
    std::vector<Protein> proteins = this->controller.get_all_proteins_sorted_for_given_sequence(sequence);

    if (proteins.empty()){
        std::cout<<"There are no proteins for given sequence! Add some.\n";
        return;
    }

    for(const Protein& protein: proteins)
        std::cout<<protein.to_string()<<"\n";
}

UI::UI(Controller _controller) : controller(std::move(_controller)){

}
