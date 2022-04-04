#include "DynamicArray.h"
#include <stdlib.h>

DynamicArray* create_dynamic_array(int capacity, DestroyElementFunctionType destroy_element_function)
{
	DynamicArray* dynamic_array = (DynamicArray*)malloc(sizeof(DynamicArray));
	// make sure that the space was allocated
	if (dynamic_array == NULL)
		return NULL;

	dynamic_array->capacity = capacity;
	dynamic_array->length = 0;

	// allocate space for the elements
	dynamic_array->elements = (TElement*)malloc(capacity * sizeof(TElement));
	if (dynamic_array->elements == NULL)
		return NULL;

	// initialize the function pointer
	dynamic_array->elements_destroyer = destroy_element_function;

	return dynamic_array;
}

TElement get_element(DynamicArray* array, int position)
{
	if (array == NULL || position < 0)
		return NULL;

	return array->elements[position];
}

int resize_dynamic_array(DynamicArray* array)
{
	if (array == NULL)
		return -1;

	array->capacity *= 2;

	TElement* auxiliary_array = (TElement*)malloc(array->capacity * sizeof(TElement));
	if (auxiliary_array == NULL)
		return -1;

	for (int i = 0; i < array->length; i++)
		auxiliary_array[i] = array->elements[i];
	
	free(array->elements);
	array->elements = auxiliary_array;

	return 0;
}

void add_element(DynamicArray* array, TElement new_element)
{
	if (array == NULL)
		return;
	
	if (array->elements == NULL)
		return;

	// resize the array, if necessary
	if (array->length == array->capacity)
		resize_dynamic_array(array);

	array->elements[array->length++] = new_element;
}

void remove_element(DynamicArray* array, int position)
{
	if (array == NULL || position < 0 || position >= array->length)
		return;

	array->elements_destroyer(array->elements[position]);

	if (position != array->length - 1)
		array->elements[position] = array->elements[array->length - 1];

	array->length--;
}

int get_array_length(DynamicArray* array)
{
	if (array == NULL)
		return -1;

	return array->length;
}

void destroy_dynamic_array(DynamicArray* array)
{
	if (array == NULL)
		return;

	// deallocate each of the elements - if we decide that the dynamic array is responsible with this
	for (int i = 0; i < array->length; i++)
		array->elements_destroyer(array->elements[i]);

	// free the space allocated for the elements
	free(array->elements);
	array->elements = NULL;

	// free the space allocated for the dynamic array
	free(array);
	array = NULL;
}
