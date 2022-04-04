#pragma once
#include "Estate.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* estate_list;
} Repository;

Repository* create_repository();

int get_repository_length(Repository* repository);

int add_estate(Repository* repository, Estate* estate);

int remove_estate(Repository* repository, char* address);

int update_estate(Repository* repository, char* new_type, char* address, double new_surface, double new_price);

Estate* find_by_address(Repository* repository, char* address);

Estate* get_estate_on_given_position(Repository* repository, int position);

Estate* get_estate_list(Repository* repository);

void destroy_repository(Repository* repository);