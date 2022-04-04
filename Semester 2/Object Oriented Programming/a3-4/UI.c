#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COMMAND_LENGTH 128
#define DELIMITERS " \n"

UI* create_ui(Controller* controller)
{
    UI* ui = malloc(sizeof(UI));

    if (ui == NULL)
        return NULL;

    ui->controller = controller;

    return ui;
}

void display_menu()
{
    printf("> add <type> <address> <surface> <price>\n");
    printf("> delete <address>\n");
    printf("> update <new type> <address> <new surface> <new price>\n");
    printf("> display <address>\n");
    printf("> filter\n");
    printf("> undo\n");
    printf("> redo\n");
    printf("> exit\n\n");
    printf("> ");
}

void display_filter_menu()
{
    printf("> <1> for estates of given type and having surface greater than given value\n");
    printf("> <2> for estates of given type and containing given substring address\n");
    printf("> <3> for estates of given type and having the price smaller than given value\n\n");
    printf("> ");
}

void string_to_lowercase(char* string) {
    for (int index = 0; index < strlen(string); index++)
        if (string[index] >= 65 && string[index] <= 90)
            string[index] = string[index] + 32;
}

int check_empty_line(char* string) {
    if (strcmp(string, "\n") == 0)
        return 0;

    int number_of_whitespaces = 0;

    for (int index = 0; index <= strlen(string); index++)
        if (isspace(string[index]))
            number_of_whitespaces++;

    if (number_of_whitespaces == strlen(string))
        return 0;

    return 1;
}


int check_valid_type(char* string) {
    string_to_lowercase(string);

    if (strcmp(string, "house") == 0 || strcmp(string, "apartment") == 0 || strcmp(string, "penthouse") == 0)
        return 1;

    return 0;
}

void run_program(UI* ui)
{
    char input_command[COMMAND_LENGTH];
    int valid_input = 1;

    printf("Welcome to Evelyn's Real Estate Agency! Choose between commands below:\n");

    while (valid_input) {
        display_menu();
        fgets(input_command, COMMAND_LENGTH, stdin);

        if (!check_empty_line(input_command))
            continue;

        char* command_argument = strtok(input_command, DELIMITERS), * auxiliary_pointer;
        string_to_lowercase(command_argument);

        if (strcmp(command_argument, "add") == 0) {

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }

            if (!check_valid_type(command_argument)) {
                printf("Not a valid type! Choose between 'house', 'apartment' or 'penthouse'!\n\n");
                continue;
            }
            char* type = command_argument;

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }
            char* address = command_argument;

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }
            double surface = (double)strtod(command_argument, &auxiliary_pointer);

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }
            double price = (double)strtod(command_argument, &auxiliary_pointer);

            if (price == 0 || surface == 0) {
                printf("For price and surface you need to provide numbers!\n\n");
                continue;
            }

            if (add_estate_to_controller(ui->controller, type, address, surface, price) == -1)
                printf("The estate hasn't been added! The address provided is already used.\n\n");

            else 
                printf("The estate has been successfully added!\n\n");
        }

        else if (strcmp(command_argument, "delete") == 0) {

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }
            char* address = command_argument;

            if (remove_estate_from_controller(ui->controller, address) == -1)
                printf("The estate hasn't been removed! The address provided is not used.\n\n");

            else
                printf("The estate has been successfully removed!\n\n");
        }

        else if (strcmp(command_argument, "update") == 0) {

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }

            if (!check_valid_type(command_argument)) {
                printf("Not a valid type! Choose between 'house', 'apartment' or 'penthouse'!\n\n");
                continue;
            }
            char* new_type = command_argument;

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }
            char* address = command_argument;

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }
            double new_surface = (double)strtod(command_argument, &auxiliary_pointer);

            command_argument = strtok(NULL, DELIMITERS);
            if (command_argument == NULL) {
                printf("Not enough arguments! See the menu again.\n\n");
                continue;
            }
            double new_price = (double)strtod(command_argument, &auxiliary_pointer);

            if (new_price == 0 || new_surface == 0) {
                printf("For price and surface you need to provide numbers!\n\n");
                continue;
            }

            if (update_estate_from_controller(ui->controller, new_type, address, new_surface, new_price) == -1)
                printf("The estate hasn't been updated! The address provided is not used.\n\n");

            else
                printf("The estate has been successfully updated!\n\n");
        }

        else if (strcmp(command_argument, "display") == 0) {
            command_argument = strtok(NULL, DELIMITERS);

            int number_of_estates;
            Estate* list_of_estates;

            if (command_argument == NULL)
                list_of_estates = get_controller_estate_list(ui->controller, &number_of_estates);

            else
                list_of_estates = get_controller_estate_list_containing_address_substring(ui->controller, &number_of_estates, command_argument);

            if (number_of_estates == 0)
                printf("There are no estates for the asked operation! Add some new estates.\n\n");
            
            else {
                char sort_type[COMMAND_LENGTH];

                printf("> <ascending>/<descending>/<unsorted>\n\n");
                printf("> ");
                fgets(sort_type, COMMAND_LENGTH, stdin);

                char* sort_type_given = strtok(sort_type, DELIMITERS);

                if (!manual_strcasecmp(sort_type_given, "ascending"))
                    sort_estate_list_ascending_order_price(list_of_estates, number_of_estates);

                else if (!manual_strcasecmp(sort_type_given, "descending"))
                    sort_estate_list_descending_order_price(list_of_estates, number_of_estates);

                else if (manual_strcasecmp(sort_type_given, "unsorted")) {
                    printf("\n");
                    free(list_of_estates);
                    continue;
                }

                printf("------------------------------------\n");
                printf("| type : address : surface : price |\n");
                printf("------------------------------------\n");

                for (int index = 0; index < number_of_estates; index++) {
                    Estate* estate = &list_of_estates[index];
                    printf("%s : %s : %.1f : %.1f\n", get_type(estate), get_address(estate), get_surface(estate), get_price(estate));
                }

                printf("\n");
            }
            free(list_of_estates);
        }

        else if (strcmp(command_argument, "filter") == 0) {
            char filter_type[COMMAND_LENGTH];

            display_filter_menu();
            fgets(filter_type, COMMAND_LENGTH, stdin);

            char* filter_type_given = strtok(filter_type, DELIMITERS);

            if (strcmp(filter_type_given, "1") && strcmp(filter_type_given, "2") && strcmp(filter_type_given, "3"))
                continue;

            int number_of_estates;
            Estate* list_of_estates = NULL;

            char filter_command[COMMAND_LENGTH];

            if (!strcmp(filter_type_given, "1")) {
                printf("> <type> <surface>\n\n");
                printf("> ");

                fgets(filter_command, COMMAND_LENGTH, stdin);

                char* filter_argument = strtok(filter_command, DELIMITERS);

                if (filter_argument == NULL) {
                    printf("Not enough arguments! See the menu again.\n\n");
                    continue;
                }

                if (!check_valid_type(filter_argument)) {
                    printf("Not a valid type! Choose between 'house', 'apartment' or 'penthouse'!\n\n");
                    continue;
                }
                char* type = filter_argument;

                filter_argument = strtok(NULL, DELIMITERS);

                if (filter_argument == NULL) {
                    printf("Not enough arguments! See the menu again.\n\n");
                    continue;
                }

                double surface = (double)strtod(filter_argument, &auxiliary_pointer);

                list_of_estates = get_controller_estate_list_of_given_type_having_surface_greater_than_given_value(ui->controller, &number_of_estates, type, surface);
            }

            else if (!strcmp(filter_type_given, "2")) {
                printf("> <type> <address>\n\n");
                printf("> ");

                fgets(filter_command, COMMAND_LENGTH, stdin);

                char* filter_argument = strtok(filter_command, DELIMITERS);

                if (filter_argument == NULL) {
                    printf("Not enough arguments! See the menu again.\n\n");
                    continue;
                }

                if (!check_valid_type(filter_argument)) {
                    printf("Not a valid type! Choose between 'house', 'apartment' or 'penthouse'!\n\n");
                    continue;
                }
                char* type = filter_argument;

                filter_argument = strtok(NULL, DELIMITERS);

                if (filter_argument == NULL) {
                    printf("Not enough arguments! See the menu again.\n\n");
                    continue;
                }

                char* address = filter_argument;

                list_of_estates = get_controller_estate_list_of_given_type_containing_address_substring(ui->controller, &number_of_estates, type, address);
            }

            else if (!strcmp(filter_type_given, "3")) {
                printf("> <type> <price>\n\n");
                printf("> ");

                fgets(filter_command, COMMAND_LENGTH, stdin);

                char* filter_argument = strtok(filter_command, DELIMITERS);

                if (filter_argument == NULL) {
                    printf("Not enough arguments! See the menu again.\n\n");
                    continue;
                }

                if (!check_valid_type(filter_argument)) {
                    printf("Not a valid type! Choose between 'house', 'apartment' or 'penthouse'!\n\n");
                    continue;
                }
                char* type = filter_argument;

                filter_argument = strtok(NULL, DELIMITERS);

                if (filter_argument == NULL) {
                    printf("Not enough arguments! See the menu again.\n\n");
                    continue;
                }

                double price = (double)strtod(filter_argument, &auxiliary_pointer);

                list_of_estates = get_controller_estate_list_of_given_type_having_price_smaller_than_given_value(ui->controller, &number_of_estates, type, price);
            }

            if (number_of_estates == 0)
                printf("There are no estates for the asked operation! Add some new estates.\n\n");

            else {
                char sort_type[COMMAND_LENGTH];

                printf("> <ascending>/<descending>/<unsorted>\n\n");
                printf("> ");
                fgets(sort_type, COMMAND_LENGTH, stdin);

                char* sort_type_given = strtok(sort_type, DELIMITERS);

                if (!manual_strcasecmp(sort_type_given, "ascending"))
                    sort_estate_list_ascending_order_price(list_of_estates, number_of_estates);

                else if (!manual_strcasecmp(sort_type_given, "descending"))
                    sort_estate_list_descending_order_price(list_of_estates, number_of_estates);

                else if (manual_strcasecmp(sort_type_given, "unsorted")) {
                    printf("\n");
                    free(list_of_estates);
                    continue;
                }

                printf("------------------------------------\n");
                printf("| type : address : surface : price |\n");
                printf("------------------------------------\n");

                for (int index = 0; index < number_of_estates; index++) {
                    Estate* estate = &list_of_estates[index];
                    printf("%s : %s : %.1f : %.1f\n", get_type(estate), get_address(estate), get_surface(estate), get_price(estate));
                }

                printf("\n");

                free(list_of_estates);
            }
        }

        else if (strcmp(command_argument, "undo") == 0) {
            int undo_status = undo(ui->controller);

            if (undo_status == -1)
                printf("There are no more operations to be undone!\n\n");
            else
                printf("The operation has been succesfully undone!\n\n");
        }
        
        else if (strcmp(command_argument, "redo") == 0) {
            int redo_status = redo(ui->controller);

            if (redo_status == -1)
                printf("There are no more operations to be redone!\n\n");
            else
                printf("The operation has been succesfully redone!\n\n");
        }

        else if (strcmp(command_argument, "exit") == 0)
            valid_input = 0;
    }

}

void destroy_ui(UI* ui)
{
    destroy_controller(ui->controller);
    free(ui);
}
