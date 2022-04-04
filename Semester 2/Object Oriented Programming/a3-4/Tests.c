#include "Tests.h"
#include "Estate.h"
#include "Repository.h"
#include "Controller.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"

void test_domain__check_getters__successfully_working() 
{
	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	assert(!strcmp(get_type(estate), "house"));
	assert(!strcmp(get_address(estate), "1039CoburnHollowRoad"));
	assert(get_surface(estate) == 300.5);
	assert(get_price(estate) == 2250000);

	destroy_estate(estate);
}

void test_domain__check_setters__successfully_working()
{
	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	set_type(estate, "penthouse");
	set_surface(estate, 500);
	set_price(estate, 6250000.76);

	assert(!strcmp(get_type(estate), "penthouse"));
	assert(!strcmp(get_address(estate), "1039CoburnHollowRoad"));
	assert(get_surface(estate) == 500);
	assert(get_price(estate) == 6250000.76);

	destroy_estate(estate);
}

void test_domain__check_copy__successfully_working()
{
	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	Estate* estate_copy = copy_estate(estate);

	assert(estate != estate_copy);
	assert(estate->type != estate_copy->type);
	assert(estate->address != estate_copy->address);

	assert(!strcmp(get_type(estate), get_type(estate_copy)));
	assert(!strcmp(get_address(estate), get_address(estate_copy)));
	assert(get_surface(estate) == get_surface(estate_copy));
	assert(get_price(estate) == get_price(estate_copy));

	destroy_estate(estate);
	destroy_estate(estate_copy);
}

void test_domain()
{
	test_domain__check_getters__successfully_working();
	test_domain__check_setters__successfully_working();
	test_domain__check_copy__successfully_working();
}

void test_repository__add_new_estate__successfully_added()
{
	Repository* repository = create_repository();

	assert(get_repository_length(repository) == 0);

	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	int process_status = add_estate(repository, estate);

	assert(process_status == 0);
	assert(get_repository_length(repository) == 1);

	destroy_repository(repository);
}

void test_repository__add_nonexistent_estate__returns_expected_value()
{
	Repository* repository = create_repository();

	Estate* estate = NULL;

	assert(get_repository_length(repository) == 0);

	int process_status = add_estate(repository, estate);

	assert(process_status == -1);
	assert(get_repository_length(repository) == 0);

	destroy_repository(repository);
}

void test_repository__remove_existent_estate__successfully_removed()
{
	Repository* repository = create_repository();

	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	add_estate(repository, estate);

	assert(get_repository_length(repository) == 1);

	int process_status = remove_estate(repository, "1039CoburnHollowRoad");

	assert(process_status == 0);
	assert(get_repository_length(repository) == 0);

	destroy_repository(repository);
}

void test_repository__remove_nonexistent_estate__returns_expected_value()
{
	Repository* repository = create_repository();

	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	add_estate(repository, estate);

	assert(get_repository_length(repository) == 1);

	int process_status = remove_estate(repository, "random address");

	assert(process_status == -1);
	assert(get_repository_length(repository) == 1);

	destroy_repository(repository);
}

void test_repository__update_existent_address__successfully_updated()
{
	Repository* repository = create_repository();

	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	add_estate(repository, estate);

	assert(get_repository_length(repository) == 1);

	int process_status = update_estate(repository, "penthouse", "1039CoburnHollowRoad", 500, 6250000.76);

	assert(process_status == 0);
	assert(get_repository_length(repository) == 1);

	Estate* updated_estate = find_by_address(repository, "1039CoburnHollowRoad");

	assert(!strcmp(get_type(updated_estate), "penthouse"));
	assert(!strcmp(get_address(updated_estate), "1039CoburnHollowRoad"));
	assert(get_surface(updated_estate) == 500);
	assert(get_price(updated_estate) == 6250000.76);

	destroy_repository(repository);
}

void test_repository__update_nonexistent_address__returns_expected_value()
{
	Repository* repository = create_repository();

	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);

	add_estate(repository, estate);

	assert(get_repository_length(repository) == 1);

	int process_status = update_estate(repository, "penthouse", "random address", 500, 6250000.76);

	assert(process_status == -1);
	assert(get_repository_length(repository) == 1);

	Estate* updated_estate = find_by_address(repository, "1039CoburnHollowRoad");

	assert(!strcmp(get_type(estate), "house"));
	assert(!strcmp(get_address(estate), "1039CoburnHollowRoad"));
	assert(get_surface(estate) == 300.5);
	assert(get_price(estate) == 2250000);

	destroy_repository(repository);
}

void test_repository__find_by_nonexistent_address__returns_expected_value()
{
	Repository* repository = create_repository();

	assert(find_by_address(repository, NULL) == NULL);

	destroy_repository(repository);
}

void test_repository__get_estate_list__successfully_returns_list()
{
	Repository* repository = create_repository();

	assert(get_repository_length(repository) == 0);

	Estate* estate = create_estate("house", "1039CoburnHollowRoad", 300.5, 2250000);
	add_estate(repository, estate);

	Estate* another_estate = create_estate("penthouse", "4264HickoryLane", 500, 6250000.76);
	add_estate(repository, another_estate);

	Estate* estate_list = get_estate_list(repository);
	int length = get_repository_length(repository);

	assert(length == 2);

	assert(!strcmp(get_type(&estate_list[0]), "house"));
	assert(!strcmp(get_address(&estate_list[0]), "1039CoburnHollowRoad"));
	assert(get_surface(&estate_list[0]) == 300.5);
	assert(get_price(&estate_list[0]) == 2250000);

	assert(!strcmp(get_type(&estate_list[1]), "penthouse"));
	assert(!strcmp(get_address(&estate_list[1]), "4264HickoryLane"));
	assert(get_surface(&estate_list[1]) == 500);
	assert(get_price(&estate_list[1]) == 6250000.76);

	destroy_repository(repository);
	free(estate_list);
}

void test_repository()
{
	test_repository__add_new_estate__successfully_added();
	test_repository__add_nonexistent_estate__returns_expected_value();
	test_repository__remove_existent_estate__successfully_removed();
	test_repository__remove_nonexistent_estate__returns_expected_value();
	test_repository__update_existent_address__successfully_updated();
	test_repository__update_nonexistent_address__returns_expected_value();
	test_repository__find_by_nonexistent_address__returns_expected_value();
	test_repository__get_estate_list__successfully_returns_list();
}

void test_controller__add_estate__valid_input__successfully_added_to_list()
{
    Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

    char* type = "house";
    char* address = "1521ProvidenceLane";
    double surface = 120.5;
    double price = 300000;

    add_estate_to_controller(controller, type, address, surface, price);

    int number_of_estates;
    Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	Estate* first_estate = &estate_list[0];

	assert(number_of_estates == 1);

	assert(!strcmp(get_type(first_estate), type));
	assert(!strcmp(get_address(first_estate), address));
	assert(get_surface(first_estate) == 120.5);
	assert(get_price(first_estate) == 300000);

    destroy_controller(controller);
	free(estate_list);
}

void test_controller__add_estate__existent_address__estate_not_added()
{
    Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

    char* type = "house";
    char* address = "1521ProvidenceLane";
    double surface = 120.5;
    double price = 300000;

    add_estate_to_controller(controller, type, address, surface, price);

    char* another_type = "penthouse";
    char* same_address = "1521providencelane";
    double another_surface = 250.71;
    double another_price = 3500000;

	int process_status = add_estate_to_controller(controller, another_type, same_address, another_surface, another_price);

	int number_of_estates;
	Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	assert(process_status == -1);
	assert(number_of_estates == 1);

    destroy_controller(controller);
	free(estate_list);
}

void test_controller__remove_estate__valid_input__successfully_removed_from_list()
{
    Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

    char* type = "house";
    char* address = "1521 Providence Lane";
    double surface = 120.5;
    double price = 300000;

    add_estate_to_controller(controller, type, address, surface, price);

    int remove_action_status = remove_estate_from_controller(controller, address);

    int number_of_estates;
    Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	assert(remove_action_status == 0);
	assert(number_of_estates == 0);

    destroy_controller(controller);
	free(estate_list);
}

void test_controller__remove_gear__nonexistent_address__estate_not_removed()
{
    Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

    char* type = "house";
    char* address = "1521 Providence Lane";
    double surface = 120.5;
    double price = 300000;

    add_estate_to_controller(controller, type, address, surface, price);

    char* nonexistent_address = "228 Terra Street";

    int remove_action_status = remove_estate_from_controller(controller, nonexistent_address);

    int number_of_estates;
    Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	assert(remove_action_status == -1);
	assert(number_of_estates == 1);

    destroy_controller(controller);
	free(estate_list);
}

void test_controller__update_estate__valid_input__successfully_updates_estate()
{
    Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

    char* type = "house";
    char* address = "1521 Providence Lane";
    double surface = 120.5;
    double price = 300000;

    add_estate_to_controller(controller, type, address, surface, price);

    char* new_type = "penthouse";
    double new_surface = 250.71;
    double new_price = 3500000;

    int update_action_status = update_estate_from_controller(controller, new_type, address, new_surface, new_price);

    int number_of_estates;
    Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	assert(update_action_status == 0);

	assert(strcmp(get_type(&estate_list[0]), new_type) == 0);
	assert(strcmp(get_address(&estate_list[0]), address) == 0);
	assert(get_surface(&estate_list[0]) == new_surface);
	assert(get_price(&estate_list[0]) == new_price);

    destroy_controller(controller);
	free(estate_list);
}

void test_controller__update_estate__nonexistent_address__throws_exception()
{
    Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

    char* type = "house";
    char* address = "1521 Providence Lane";
    double surface = 120.5;
    double price = 300000;

    add_estate_to_controller(controller, type, address, surface, price);

    char* new_type = "penthouse";
    char* another_address = "228 Terra Street";
    double new_surface = 250.71;
    double new_price = 3500000;

    int update_status = update_estate_from_controller(controller, new_type, another_address, new_surface, new_price);

    int number_of_estates;
    Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	assert(update_status == -1);

	assert(strcmp(get_type(&estate_list[0]), type) == 0);
	assert(strcmp(get_address(&estate_list[0]), address) == 0);
	assert(get_surface(&estate_list[0]) == surface);
	assert(get_price(&estate_list[0]) == price);

    destroy_controller(controller);
	free(estate_list);
}

void test_controller__sort_estate_list_ascending_order_price__list_successfully_ordered()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	add_estates_entries_at_application_startup(controller);

	int number_of_estates;
	Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	sort_estate_list_ascending_order_price(estate_list, number_of_estates);

	assert(number_of_estates == 10);

	assert(get_price(&estate_list[0]) == 250000);
	assert(get_price(&estate_list[1]) == 300000);
	assert(get_price(&estate_list[2]) == 347000);
	assert(get_price(&estate_list[3]) == 500000);
	assert(get_price(&estate_list[4]) == 1800000);
	assert(get_price(&estate_list[5]) == 2200000);
	assert(get_price(&estate_list[6]) == 2890000);
	assert(get_price(&estate_list[7]) == 3000000);
	assert(get_price(&estate_list[8]) == 5000000);
	assert(get_price(&estate_list[9]) == 5000000);

	destroy_controller(controller);
	free(estate_list);
}

void test_controller__sort_estate_list_descending_order_price__list_successfully_ordered()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	add_estates_entries_at_application_startup(controller);

	int number_of_estates;
	Estate* estate_list = get_controller_estate_list(controller, &number_of_estates);

	sort_estate_list_descending_order_price(estate_list, number_of_estates);

	assert(number_of_estates == 10);

	assert(get_price(&estate_list[0]) == 5000000);
	assert(get_price(&estate_list[1]) == 5000000);
	assert(get_price(&estate_list[2]) == 3000000);
	assert(get_price(&estate_list[3]) == 2890000);
	assert(get_price(&estate_list[4]) == 2200000);
	assert(get_price(&estate_list[5]) == 1800000);
	assert(get_price(&estate_list[6]) == 500000);
	assert(get_price(&estate_list[7]) == 347000);
	assert(get_price(&estate_list[8]) == 300000);
	assert(get_price(&estate_list[9]) == 250000);

	destroy_controller(controller);
	free(estate_list);
}

void test_controller__filter_estate_list_to_contain_address_substring__successfully_filtered()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	add_estates_entries_at_application_startup(controller);

	char* searched_address = "drive";
	int number_of_estates;
	Estate* filtered_estate_list = get_controller_estate_list_containing_address_substring(controller, &number_of_estates, searched_address);

	sort_estate_list_ascending_order_price(filtered_estate_list, number_of_estates);

	assert(number_of_estates == 3);

	assert(!strcmp(get_address(&filtered_estate_list[0]), "207ThompsonDrive"));
	assert(!strcmp(get_address(&filtered_estate_list[1]), "398FlaniganOaksDrive"));
	assert(!strcmp(get_address(&filtered_estate_list[2]), "2298KildeerDrive"));

	destroy_controller(controller);
	free(filtered_estate_list);
}

void test_controller__filter_estate_list_by_given_type_having_surface_greater_than_given_value__successfully_filtered()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	add_estates_entries_at_application_startup(controller);

	char* given_type = "apartment";
	double given_surface = 62;
	int number_of_estates;
	Estate* filtered_estate_list = get_controller_estate_list_of_given_type_having_surface_greater_than_given_value(controller, &number_of_estates, given_type, given_surface);

	sort_estate_list_ascending_order_price(filtered_estate_list, number_of_estates);

	assert(number_of_estates == 2);

	assert(get_surface(&filtered_estate_list[0]) == 80.48);
	assert(get_surface(&filtered_estate_list[1]) == 121.3);

	destroy_controller(controller);
	free(filtered_estate_list);
}

void test_controller__filter_estate_list_of_given_type_to_contain_given_address_substring__successfully_filtered()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	add_estates_entries_at_application_startup(controller);

	char* given_type = "apartment";
	char* given_substring_address = "r";
	int number_of_estates;
	Estate* filtered_estate_list = get_controller_estate_list_of_given_type_containing_address_substring(controller, &number_of_estates, given_type, given_substring_address);

	sort_estate_list_ascending_order_price(filtered_estate_list, number_of_estates);

	assert(number_of_estates == 3);
	
	assert(!strcmp(get_address(&filtered_estate_list[0]), "4611NormanStreet"));
	assert(!strcmp(get_address(&filtered_estate_list[1]), "207ThompsonDrive"));
	assert(!strcmp(get_address(&filtered_estate_list[2]), "1685RedDogRoad"));

	destroy_controller(controller);
	free(filtered_estate_list);
}

void test_controller__filter_estate_list_of_given_type_having_price_smaller_than_given_value__successfully_filtered()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	add_estates_entries_at_application_startup(controller);

	char* given_type = "house";
	double given_price = 2250000;
	int number_of_estates;
	Estate* filtered_estate_list = get_controller_estate_list_of_given_type_having_price_smaller_than_given_value(controller, &number_of_estates, given_type, given_price);

	sort_estate_list_ascending_order_price(filtered_estate_list, number_of_estates);

	assert(number_of_estates == 2);

	assert(get_price(&filtered_estate_list[0]) == 1800000);
	assert(get_price(&filtered_estate_list[1]) == 2200000);

	destroy_controller(controller);
	free(filtered_estate_list);
}

void test_controller()
{
    test_controller__add_estate__valid_input__successfully_added_to_list();
    test_controller__add_estate__existent_address__estate_not_added();
    test_controller__remove_estate__valid_input__successfully_removed_from_list();
    test_controller__remove_gear__nonexistent_address__estate_not_removed();
    test_controller__update_estate__valid_input__successfully_updates_estate();
    test_controller__update_estate__nonexistent_address__throws_exception();
	test_controller__sort_estate_list_ascending_order_price__list_successfully_ordered();
	test_controller__sort_estate_list_descending_order_price__list_successfully_ordered();
	test_controller__filter_estate_list_to_contain_address_substring__successfully_filtered();
	test_controller__filter_estate_list_by_given_type_having_surface_greater_than_given_value__successfully_filtered();
	test_controller__filter_estate_list_of_given_type_to_contain_given_address_substring__successfully_filtered();
	test_controller__filter_estate_list_of_given_type_having_price_smaller_than_given_value__successfully_filtered();
}

void test_undo__undo_add__successfully_undone()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	char* type = "house";
	char* address = "1521ProvidenceLane";
	double surface = 120.5;
	double price = 300000;

	add_estate_to_controller(controller, type, address, surface, price);

	char* another_type = "penthouse";
	char* another_address = "228 Terra Street";
	double another_surface = 250.71;
	double another_price = 3500000;

	add_estate_to_controller(controller, another_type, another_address, another_surface, another_price);

	int number_of_estates;
	Estate* estate_list_after_two_additions = get_controller_estate_list(controller, &number_of_estates);

	int undo_status;

	assert(number_of_estates == 2);

	undo_status = undo(controller);

	Estate* estate_list_after_one_undo = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 1);
	assert(undo_status == 0);

	undo_status = undo(controller);

	Estate* estate_list_after_two_undos = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 0);
	assert(undo_status == 0);

	undo_status = undo(controller);

	assert(undo_status == -1);

	destroy_controller(controller);
	free(estate_list_after_two_additions);
	free(estate_list_after_one_undo);
	free(estate_list_after_two_undos);
}

void test_undo__undo_add_remove__successfully_undone()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	char* type = "house";
	char* address = "1521ProvidenceLane";
	double surface = 120.5;
	double price = 300000;

	add_estate_to_controller(controller, type, address, surface, price);

	char* another_type = "penthouse";
	char* another_address = "228 Terra Street";
	double another_surface = 250.71;
	double another_price = 3500000;

	add_estate_to_controller(controller, another_type, another_address, another_surface, another_price);

	int number_of_estates;
	Estate* estate_list_after_two_additions = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 2);

	int undo_status;

	remove_estate_from_controller(controller, address);
	remove_estate_from_controller(controller, another_address);

	Estate* estate_list_after_two_removals = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 0);

	undo_status = undo(controller);

	Estate* estate_list_after_one_undo = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 1);
	assert(undo_status == 0);

	undo_status = undo(controller);

	Estate* estate_list_after_two_undos = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 2);
	assert(undo_status == 0);

	Estate* estate_list_after_three_undos = get_controller_estate_list(controller, &number_of_estates);

	undo_status = undo(controller);

	assert(undo_status == 0);

	undo_status = undo(controller);

	Estate* initial_estate_list = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 0);
	assert(undo_status == 0);

	undo_status = undo(controller);

	assert(undo_status == -1);

	destroy_controller(controller);
	free(estate_list_after_two_additions);
	free(estate_list_after_two_removals);
	free(estate_list_after_one_undo);
	free(estate_list_after_two_undos);
	free(estate_list_after_three_undos);
	free(initial_estate_list);
}

void test_undo__undo_redo_add__successfully_undone_redone()
{
	Repository* repository = create_repository();
	OperationStack* undo_stack = create_operation_stack();
	OperationStack* redo_stack = create_operation_stack();
	Controller* controller = create_controller(repository, undo_stack, redo_stack);

	char* type = "house";
	char* address = "1521ProvidenceLane";
	double surface = 120.5;
	double price = 300000;

	add_estate_to_controller(controller, type, address, surface, price);

	int number_of_estates;
	Estate* estate_list_after_two_additions = get_controller_estate_list(controller, &number_of_estates);

	int undo_redo_status;

	assert(number_of_estates == 1);

	undo_redo_status = undo(controller);

	Estate* estate_list_after_undo = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 0);
	assert(undo_redo_status == 0);

	undo_redo_status = redo(controller);

	Estate* estate_list_after_redo = get_controller_estate_list(controller, &number_of_estates);

	assert(number_of_estates == 1);
	assert(undo_redo_status == 0);

	undo_redo_status = undo(controller);

	assert(undo_redo_status == 0);

	undo_redo_status = undo(controller);

	assert(undo_redo_status == -1);

	destroy_controller(controller);
	free(estate_list_after_two_additions);
	free(estate_list_after_undo);
	free(estate_list_after_redo);
}

void test_undo_redo()
{
	test_undo__undo_add__successfully_undone();
	test_undo__undo_add_remove__successfully_undone();
	test_undo__undo_redo_add__successfully_undone_redone();
}

void test_all_functionalities()
{
	test_domain();
	test_repository();
	test_controller();
	test_undo_redo();
}
