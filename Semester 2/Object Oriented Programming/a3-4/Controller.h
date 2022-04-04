#pragma once
#include "Repository.h"
#include "OperationStack.h"

typedef struct
{
	Repository* repository;

	char* type_filter;
	char* address_filter;
	double price_filter;
	double surface_filter;

	OperationStack* undo_stack;
	OperationStack* redo_stack;

	Repository* undo_updates;

} Controller;

Controller* create_controller(Repository* repository, OperationStack* undo_stack, OperationStack* redo_stack);

int manual_strcasecmp(const char* first_string, const char* second_string);

int add_estate_to_controller(Controller* controller, char* type, char* address, double surface, double price);

int remove_estate_from_controller(Controller* controller, char* address);

int update_estate_from_controller(Controller* controller, char* new_type, char* address, double new_surface, double new_price);

Estate* get_controller_estate_list(Controller* controller, int* length);

Estate* get_controller_estate_list_containing_address_substring(Controller* controller, int* length, char* address);

Estate* get_controller_estate_list_of_given_type_having_surface_greater_than_given_value(Controller* controller, int* length, char* type, double surface);

Estate* get_controller_estate_list_of_given_type_containing_address_substring(Controller* controller, int* length, char* type, char* address);

Estate* get_controller_estate_list_of_given_type_having_price_smaller_than_given_value(Controller* controller, int* length, char* type, double price);

void sort_estate_list_ascending_order_price(Estate* estate_list, int number_of_estates);

void sort_estate_list_descending_order_price(Estate* estate_list, int number_of_estates);

void add_estates_entries_at_application_startup(Controller* controller);

int undo(Controller* controller);

int redo(Controller* controller);

void destroy_controller(Controller* controller);