#pragma once

typedef void* TElement;
typedef void (*DestroyElementFunctionType)(void*);

typedef struct
{
	TElement* elements;

	int length;
	int capacity;

	DestroyElementFunctionType elements_destroyer;

} DynamicArray;

DynamicArray* create_dynamic_array(int capacity, DestroyElementFunctionType destroy_element_function);

TElement get_element(DynamicArray* array, int position);

void add_element(DynamicArray* array, TElement new_element);

void remove_element(DynamicArray* array, int position);

int get_array_length(DynamicArray* array);

void destroy_dynamic_array(DynamicArray* array);
