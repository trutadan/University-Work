#include "OperationStack.h"
#include <stdlib.h>

OperationStack* create_operation_stack() {
	OperationStack* operations_stack = malloc(sizeof(OperationStack));
	if (operations_stack == NULL)
		return NULL;

	operations_stack->operations = create_dynamic_array(10, &destroy_operation);
	if (operations_stack->operations == NULL)
		return NULL;

	return operations_stack;
}

void push(OperationStack* operations_stack, Operation* operation) {
	add_element(operations_stack->operations, operation);
}

Operation* pop(OperationStack* operations_stack) {
	int position = get_array_length(operations_stack->operations) - 1;
	
	Operation* operation = copy_operation(get_element(operations_stack->operations, position));
	remove_element(operations_stack->operations, position);
	
	return operation;
}

int is_empty(OperationStack* operations_stack) {
	return get_array_length(operations_stack->operations) == 0;
}

void destroy_operation_stack(OperationStack* operations_stack) {
	destroy_dynamic_array(operations_stack->operations);
	free(operations_stack);
}