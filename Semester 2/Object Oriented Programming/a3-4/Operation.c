#include "Operation.h"
#include <string.h>
#include <stdlib.h>

Operation* create_operation(Estate* estate, char* operation_name)
{
    Operation* operation = malloc(sizeof(Operation));
    if (operation == NULL)
        return NULL;

    operation->estate = copy_estate(estate);
    operation->operation_name = malloc(sizeof(char) * strlen(operation_name) + 1);
    if (operation->operation_name == NULL)
        return NULL;

    strcpy(operation->operation_name, operation_name);

    return operation;
}

Estate* get_estate(Operation* operation) {
    if (operation == NULL)
        return NULL;

    return operation->estate;
}

char* get_operation_name(Operation* operation) {
    if (operation == NULL)
        return NULL;

    return operation->operation_name;
}

Operation* copy_operation(Operation* operation) {
    if (operation == NULL)
        return NULL;

    return create_operation(operation->estate, operation->operation_name);
}

void destroy_operation(Operation* operation) {
    if (operation == NULL)
        return;

    destroy_estate(operation->estate);
    
    free(operation->operation_name);
    free(operation);
}
