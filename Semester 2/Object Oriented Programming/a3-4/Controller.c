#include "Controller.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef int (*filter_function)(Controller*, Estate);

Controller* create_controller(Repository* repository, OperationStack* undo_stack, OperationStack* redo_stack)
{
	Controller* controller = (Controller*)malloc(sizeof(Controller));
	if (controller == NULL)
		return NULL;

	controller->repository = repository;
	controller->undo_updates = create_repository();
	controller->undo_stack = undo_stack;
	controller->redo_stack = redo_stack;

	return controller;
}

int manual_strcasecmp(const char* first_string, const char* second_string)
{
	int difference_between_characters = 0;
	for (; ; )
	{
		const int character_from_first_string = tolower(*first_string++);
		const int character_from_second_string = tolower(*second_string++);
		if (((difference_between_characters = character_from_first_string - character_from_second_string) != 0) || (character_from_first_string == '\0') || (character_from_second_string == '\0'))
			break;
	}
	return difference_between_characters;
}

char* manual_strcasestr(const char* first_string, const char* second_string)
{
	const char* first_string_copy = first_string;
	const char* second_string_copy = second_string;
	const char* return_value = *second_string_copy == 0 ? first_string : 0;

	while (*first_string_copy != 0 && *second_string_copy != 0)
	{
		if (tolower((unsigned char)*first_string_copy) == tolower((unsigned char)*second_string_copy))
		{
			if (return_value == 0)
				return_value = first_string_copy;

			second_string_copy++;
		}

		else
		{
			second_string_copy = second_string;
			if (return_value != 0)
				first_string_copy = return_value + 1;

			if (tolower((unsigned char)*first_string_copy) == tolower((unsigned char)*second_string_copy))
			{
				return_value = first_string_copy;
				second_string_copy++;
			}
			else
				return_value = 0;
		}

		first_string_copy++;
	}

	return *second_string_copy == 0 ? (char*)return_value : 0;
}

int check_existing_estate_address(Repository* repository, char* searched_address)
{
	Estate* estate_list = get_estate_list(repository);

	for (int index = 0; index < get_repository_length(repository); index++)
		if (!manual_strcasecmp(get_address(&estate_list[index]), searched_address)) {
			free(estate_list);
			return -1;
		}

	free(estate_list);
	return 0;
}

int add_estate_to_controller(Controller* controller, char* type, char* address, double surface, double price)
{
	if (check_existing_estate_address(controller->repository, address) == -1)
		return -1;

	Estate* estate = create_estate(type, address, surface, price);

	int operation_result = add_estate(controller->repository, estate);

	if (operation_result == 0){
		Operation* operation = create_operation(estate, "add");
		if (operation == NULL)
			return -1;

		push(controller->undo_stack, operation);
	}

	return operation_result;
}

int remove_estate_from_controller(Controller* controller, char* address)
{
	if (check_existing_estate_address(controller->repository, address) == 0)
		return -1;

	Estate* estate = find_by_address(controller->repository, address);
	Operation* operation = create_operation(estate, "remove");

	if (operation == NULL)
		return -1;
	
	else
		push(controller->undo_stack, operation);

	int operation_result = remove_estate(controller->repository, address);

	return operation_result;
}

int update_estate_from_controller(Controller* controller, char* new_type, char* address, double new_surface, double new_price)
{
	if (check_existing_estate_address(controller->repository, address) == 0)
		return -1;

	Estate* estate = find_by_address(controller->repository, address);
	Operation* operation = create_operation(estate, "update");

	if (operation == NULL)
		return -1;

	else 
		push(controller->undo_stack, operation);

	int operation_result = update_estate(controller->repository, new_type, address, new_surface, new_price);

	add_estate(controller->undo_updates, copy_estate(find_by_address(controller->repository, address)));

	return operation_result;
}

Estate* get_controller_estate_list(Controller* controller, int* length)
{
	*length = get_repository_length(controller->repository);
	return get_estate_list(controller->repository);
}

Estate* get_controller_filtered_estate_list(Controller* controller, int* length, filter_function filter_method)
{
	*length = 0;
	int capacity = 1;

	Estate* filtered_estate_list = malloc(capacity * sizeof(Estate));

	for (int index = 0; index < get_repository_length(controller->repository); index++)
		if (filter_method(controller, *(Estate*)get_element(controller->repository->estate_list, index)) == 0) {
			if (*length == capacity) {
				
				capacity *= 2;
				Estate* bigger_filtered_estate_list = malloc(capacity * sizeof(Estate));

				for (int auxiliary_index = 0; auxiliary_index < *length; auxiliary_index++)
					bigger_filtered_estate_list[auxiliary_index] = filtered_estate_list[auxiliary_index];

				free(filtered_estate_list);
				filtered_estate_list = bigger_filtered_estate_list;
			}

			filtered_estate_list[*length] = *(Estate*)get_element(controller->repository->estate_list, index);
			(*length)++;
		}

	return filtered_estate_list;
}

int check_substring_address(Controller* controller, Estate* estate)
{
	if (manual_strcasestr(get_address(estate), controller->address_filter))
		return 0;

	return -1;
}

Estate* get_controller_estate_list_containing_address_substring(Controller* controller, int* length, char* address) {
	controller->address_filter = address;
	return get_controller_filtered_estate_list(controller, length, check_substring_address);
}

int check_given_type_and_greater_surface(Controller* controller, Estate* estate)
{
	if (!manual_strcasecmp(get_type(estate), controller->type_filter) && estate->surface > controller->surface_filter)
		return 0;

	return -1;
}

Estate* get_controller_estate_list_of_given_type_having_surface_greater_than_given_value(Controller* controller, int* length, char* type, double surface) {
	controller->type_filter = type;
	controller->surface_filter = surface;
	return get_controller_filtered_estate_list(controller, length, check_given_type_and_greater_surface);
}

int check_substring_address_and_type(Controller* controller, Estate* estate)
{
	if (manual_strcasestr(get_address(estate), controller->address_filter) && !manual_strcasecmp(get_type(estate), controller->type_filter))
		return 0;

	return -1;
}

Estate* get_controller_estate_list_of_given_type_containing_address_substring(Controller* controller, int* length, char* type, char* address) {
	controller->type_filter = type;
	controller->address_filter = address;
	return get_controller_filtered_estate_list(controller, length, check_substring_address_and_type);
}

int check_given_type_and_smaller_price(Controller* controller, Estate* estate)
{
	if (!manual_strcasecmp(get_type(estate), controller->type_filter) && estate->price < controller->price_filter)
		return 0;

	return -1;
}

Estate* get_controller_estate_list_of_given_type_having_price_smaller_than_given_value(Controller* controller, int* length, char* type, double price) {
	controller->type_filter = type;
	controller->price_filter = price;
	return get_controller_filtered_estate_list(controller, length, check_given_type_and_smaller_price);
}

void sort_estate_list_ascending_order_price(Estate* estate_list, int number_of_estates)
{
	int is_list_sorted = 0;

	while (!is_list_sorted) {
		is_list_sorted = 1;

		for (int index = 0; index < number_of_estates - 1; index++)
			if (get_price(&estate_list[index]) > get_price(&estate_list[index + 1])) {
				is_list_sorted = 0;
				Estate auxiliary_estate = estate_list[index];
				estate_list[index] = estate_list[index + 1];
				estate_list[index + 1] = auxiliary_estate;
			}
	}
}

void sort_estate_list_descending_order_price(Estate* estate_list, int number_of_estates)
{
	sort_estate_list_ascending_order_price(estate_list, number_of_estates);

	int start_to_end_index = 0, end_to_start_index = number_of_estates - 1;

	while (start_to_end_index < end_to_start_index) {
		Estate auxiliary_estate = estate_list[start_to_end_index];
		estate_list[start_to_end_index] = estate_list[end_to_start_index];
		estate_list[end_to_start_index] = auxiliary_estate;

		start_to_end_index++, end_to_start_index--;
	}
}

int undo(Controller* controller)
{
	if (controller == NULL)
		return -1;

	if (is_empty(controller->undo_stack))
		return -1;

	Operation* operation = pop(controller->undo_stack);

	push(controller->redo_stack, operation);

	if (strcmp(operation->operation_name, "add") == 0)
		remove_estate(controller->repository, get_address(operation->estate));

	else if (strcmp(operation->operation_name, "remove") == 0)
		add_estate(controller->repository, copy_estate(operation->estate));

	else if (strcmp(operation->operation_name, "update") == 0)
		update_estate(controller->repository, get_type(operation->estate), get_address(operation->estate), get_surface(operation->estate), get_price(operation->estate));

	return 0;
}

int redo(Controller* controller)
{
	if (controller == NULL)
		return -1;

	if (is_empty(controller->redo_stack))
		return -1;

	Operation* operation = pop(controller->redo_stack);

	push(controller->undo_stack, operation);

	if (strcmp(operation->operation_name, "add") == 0)
		add_estate(controller->repository, copy_estate(operation->estate));

	else if (strcmp(operation->operation_name, "remove") == 0)
		remove_estate(controller->repository, get_address(operation->estate));

	else if (strcmp(operation->operation_name, "update") == 0) {
		Estate* estate = find_by_address(controller->undo_updates, get_address(operation->estate));
		update_estate(controller->repository, get_type(estate), get_address(estate), get_surface(estate), get_price(estate));
		remove_estate(controller->undo_updates, get_address(estate));
	}

	return 0;
}

void add_estates_entries_at_application_startup(Controller* controller)
{
	add_estate_to_controller(controller, "house", "3300EllaStreet", 300, 2200000);
	add_estate_to_controller(controller, "apartment", "207ThompsonDrive", 60, 300000);
	add_estate_to_controller(controller, "house", "398FlaniganOaksDrive", 220.59, 1800000);
	add_estate_to_controller(controller, "penthouse", "1108CarolynsCircle", 300, 5000000);
	add_estate_to_controller(controller, "apartment", "4611NormanStreet", 40.39, 250000);
	add_estate_to_controller(controller, "house", "2923WaybackLane", 320, 3000000);
	add_estate_to_controller(controller, "apartment", "1247LoganLane", 121.3, 500000);
	add_estate_to_controller(controller, "house", "2359BraxtonStreet", 256, 2890000);
	add_estate_to_controller(controller, "penthouse", "2298KildeerDrive", 500, 5000000);
	add_estate_to_controller(controller, "apartment", "1685RedDogRoad", 80.48, 347000);
}

void destroy_controller(Controller* controller)
{
	// first destroy the repository inside
	destroy_repository(controller->repository);
	destroy_repository(controller->undo_updates);

	destroy_operation_stack(controller->undo_stack);
	destroy_operation_stack(controller->redo_stack);

	// then free the memory
	free(controller);
}
