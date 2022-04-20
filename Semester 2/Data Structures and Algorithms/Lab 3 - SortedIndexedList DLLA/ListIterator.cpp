#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	position = list.elements.head;
}

void ListIterator::first(){
	position = list.elements.head;
}

void ListIterator::next(){
	if (!this->valid())
		throw exception();

	position = list.elements.list[position].next;
}

bool ListIterator::valid() const{
	return position != -1;
}

TComp ListIterator::getCurrent() const{
	if (!this->valid())
		throw std::exception();

	return list.elements.list[position].information;
}


