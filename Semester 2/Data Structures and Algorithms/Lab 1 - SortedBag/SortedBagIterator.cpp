#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->current = 0;
	this->element_frequency = 1;
} // theta(1) time complexity

TComp SortedBagIterator::getCurrent() const{
	if (this->current >= this->bag.number_of_elements)
		throw std::exception();

	else
		return this->bag.elements[this->current].first;
} // theta(1) time complexity

bool SortedBagIterator::valid() const{
	return (this->current < this->bag.number_of_elements);
} // theta(1) time complexity

void SortedBagIterator::next() {
	if (this->current < this->bag.number_of_elements) {
		if (this->element_frequency < this->bag.elements[current].second) {
			this->element_frequency++;
		}

		else {
			this->current++;
			this->element_frequency = 1;
			}
		}

	else
		throw std::exception();
} // theta(1) time complexity

void SortedBagIterator::first() {
	this->current = 0;
	this->element_frequency = 1;
} // theta(1) time complexity
