#include "Repository.h"
#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>

#define CAPACITY 12

Repository* create_repository()
{
    Repository* repository = (Repository*)malloc(sizeof(Repository));
    if (repository == NULL)
        return NULL;

    repository->estate_list = create_dynamic_array(CAPACITY, &destroy_estate);

    return repository;
}

int add_estate(Repository* repository, Estate* estate)
{
	if (repository == NULL || estate == NULL)
		return -1;

	add_element(repository->estate_list, estate);

	return 0;
}


int remove_estate(Repository* repository, char* address)
{
	if (repository == NULL || address == NULL)
		return -1;

	Estate* estate = find_by_address(repository, address);

	for (int index = 0; index < get_array_length(repository->estate_list); index++)
		if (get_element(repository->estate_list, index) == estate) {
			remove_element(repository->estate_list, index);
			return 0;
		}

	return -1;
}

int update_estate(Repository* repository, char* new_type, char* address, double new_surface, double new_price)
{
	if (repository == NULL)
		return -1;

	Estate* estate = find_by_address(repository, address);

	if (estate == NULL)
		return -1;

	set_type(estate, new_type);
	set_price(estate, new_price);
	set_surface(estate, new_surface);

	return 0;
}

Estate* find_by_address(Repository* repository, char* address)
{
	if (repository == NULL || address == NULL)
		return NULL;

	for (int index = 0; index < get_array_length(repository->estate_list); index++) {
		Estate* estate = get_element(repository->estate_list, index);
		if (strcmp(get_address(estate), address) == 0)
			return estate;

	}

	return NULL;
}

Estate* get_estate_on_given_position(Repository* repository, int position)
{
	if (repository == NULL)
		return NULL;

	return get_element(repository->estate_list, position);
}


int get_repository_length(Repository* repository)
{
	if (repository == NULL)
		return -1;

	return get_array_length(repository->estate_list);
}

Estate* get_estate_list(Repository* repository)
{
	int length = get_repository_length(repository);
	Estate* estate_list = malloc(length * sizeof(Estate));

	for (int index = 0; index < length; index++)
		estate_list[index] = *(Estate*)get_element(repository->estate_list, index);

	return estate_list;
}

void destroy_repository(Repository* repository)
{
	if (repository == NULL)
		return;

	// then destroy the dynamic array
	destroy_dynamic_array(repository->estate_list);
	free(repository);
}