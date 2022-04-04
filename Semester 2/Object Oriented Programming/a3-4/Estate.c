#include "Estate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Estate* create_estate(char* type, char* address, double surface, double price)
{
	Estate* estate = malloc(sizeof(Estate));
	if (estate == NULL)
		return NULL;

	estate->type = malloc(sizeof(char) * (strlen(type) + 1));
	if (estate->type != NULL)
		strcpy(estate->type, type);

	estate->address = malloc(sizeof(char) * (strlen(address) + 1));
	if (estate->address != NULL)
		strcpy(estate->address, address);

	estate->surface = surface;

	estate->price = price;

	return estate;
}

char* get_type(Estate* estate)
{
	if (estate == NULL)
		return NULL;

	return estate->type;
}

void set_type(Estate* estate, char* new_type)
{
	if (estate == NULL)
		return;

	free(estate->type);

	estate->type = malloc((strlen(new_type) + 1) * sizeof(char));

	if (estate->type != NULL)
		strcpy(estate->type, new_type);
}

char* get_address(Estate* estate)
{
	if (estate == NULL)
		return NULL;

	return estate->address;
}

double get_surface(Estate* estate)
{
	if (estate == NULL)
		return -1;

	return estate->surface;
}

void set_surface(Estate* estate, double new_surface)
{
	if (estate == NULL)
		return;

	estate->surface = new_surface;
}

double get_price(Estate* estate)
{
	if (estate == NULL)
		return -1;

	return estate->price;
}

void set_price(Estate* estate, double new_price)
{
	if (estate == NULL)
		return;

	estate->price = new_price;
}

Estate* copy_estate(Estate* estate)
{
	if (estate == NULL) {
		return NULL;
	}

	Estate* estate_copy = create_estate(estate->type, estate->address, estate->surface, estate->price);
	
	return estate_copy;
}

void destroy_estate(Estate* estate)
{
	if (estate == NULL)
		return;

	// free the memory which was allocated for the component fields
	if (estate->type != NULL)
		free(estate->type);
	
	if (estate->address != NULL)
		free(estate->address);

	// free the memory which was allocated for the planet structure
	free(estate);

	estate = NULL;
}
