#pragma once
#include "Event.h"
#include <iostream>

template <typename TypeOfElement>
class DynamicVector
{
private:
	void resize(double factor = 2);

public:
	DynamicVector(int capacity = 10);

	~DynamicVector();

	TypeOfElement& operator[](int);

	void add(TypeOfElement);

	void remove(int);

	void update(int, TypeOfElement);

	TypeOfElement* get_elements();

	int get_length() const;

private:
	TypeOfElement* elements;
	int length;
	int capacity;
};

template <typename TypeOfElement>
DynamicVector<TypeOfElement>::DynamicVector(int capacity)
{
	this->length = 0;
	this->capacity = 10;
	this->elements = new TypeOfElement[capacity];
}


template <typename TypeOfElement>
TypeOfElement& DynamicVector<TypeOfElement>::operator[](int index)
{
	return this->elements[index];
}

template <typename TypeOfElement>
void DynamicVector<TypeOfElement>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	TypeOfElement* elements = new TypeOfElement[this->capacity];
	for (int index = 0; index < this->length; index++)
		elements[index] = this->elements[index];

	delete[] this->elements;
	this->elements = elements;
}

template <typename TypeOfElement>
void DynamicVector<TypeOfElement>::add(TypeOfElement element)
{
	if (this->length == this->capacity)
		this->resize();

	this->elements[this->length] = element;
	this->length++;
}

template <typename TypeOfElement>
void DynamicVector<TypeOfElement>::remove(int remove_index)
{
	for (int index = remove_index; index < this->length - 1; index++)
		this->elements[index] = this->elements[index + 1];

	this->length--;
}

template<typename TypeOfElement>
void DynamicVector<TypeOfElement>::update(int update_index, TypeOfElement element)
{
	this->elements[update_index] = element;
}

template<typename TypeOfElement>
TypeOfElement* DynamicVector<TypeOfElement>::get_elements()
{
	return this->elements;
}

template <typename TypeOfElement>
int DynamicVector<TypeOfElement>::get_length() const
{
	return this->length;
}

template <typename TypeOfElement>
DynamicVector<TypeOfElement>::~DynamicVector()
{
	delete[] this->elements;
}