#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	this->current = 0;
} // theta(1) time complexity

void ListIterator::first(){
	this->current=0;
} // theta(1) time complexity

void ListIterator::next(){
	if (this->current >= this->list.size())
		throw exception();

	this->current++;
	this->list.first->getNext();
} // theta(1) time complexity

bool ListIterator::valid() const{
	if (this->current >= this->list.size())
		return false;

	return true;
} // theta(1) time complexity

TComp ListIterator::getCurrent() const{
	if (this->current >= this->list.size())
		throw exception();

	return this->list.getElement(this->current);
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)


