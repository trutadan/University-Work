#pragma once
#include "Estate.h"

typedef struct {
	Estate* estate;
	char* operation_name;
} Operation;

Operation* create_operation(Estate*, char*);

Estate* get_estate(Operation*);

char* get_operation_name(Operation*);

Operation* copy_operation(Operation*);

void destroy_operation(Operation*);