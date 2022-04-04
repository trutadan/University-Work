#pragma once

typedef struct {
	char* type;
	char* address;
	double surface;
	double price;
} Estate;

Estate* create_estate(char* type, char* address, double surface, double price);

char* get_type(Estate* estate);

void set_type(Estate* estate, char* new_type);

char* get_address(Estate* estate);

double get_surface(Estate* estate);

void set_surface(Estate* estate, double new_surface);

double get_price(Estate* estate);

void set_price(Estate* estate, double new_price);

Estate* copy_estate(Estate* estate);

void destroy_estate(Estate* estate);
