#pragma once
#include "Controller.h"

typedef struct {
	Controller* controller;
}UI;

UI* create_ui(Controller* controller);

void display_menu();

void string_to_lowercase(char* string);

int check_empty_line(char* string);

int check_valid_type(char* string);

void run_program(UI* ui);

void destroy_ui(UI* ui);
