#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->number_of_elements = 0;
	this->capacity = 1;
	this->elements = new ElementsPair[capacity];
	this->relation = r;
} // theta(1) time complexity


void SortedBag::add(TComp e) {
	int index = -1;

	for (int i = 0; i < this->number_of_elements; i++) {
		if (this->elements[i].first == e) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		if (this->number_of_elements == this->capacity) {
			ElementsPair* new_elements = new ElementsPair[this->capacity * 2];
			
			for (int i = 0; i < this->number_of_elements; i++)
				new_elements[i] = this->elements[i];

			delete[] this->elements;
			this->elements = new_elements;
			this->capacity *= 2;
		}

		int auxiliary_index_for_adding = -1;

		for (int i = 0; i < this->number_of_elements; i++)
			if (this->relation(e, this->elements[i].first)) {
				auxiliary_index_for_adding = i;
				break;
			}

		if (auxiliary_index_for_adding == -1) {
			elements[this->number_of_elements].first = e;
			elements[this->number_of_elements].second = 1;
		}

		else {
			for (int i = number_of_elements; i > auxiliary_index_for_adding; i--)
				elements[i] = elements[i - 1];

			elements[auxiliary_index_for_adding].first = e;
			elements[auxiliary_index_for_adding].second = 1;
		}

		this->number_of_elements++;
	}

	else 
		this->elements[index].second++;

} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- number_of_elements)


bool SortedBag::remove(TComp e) {
	int index = -1;

	for (int i = 0; i < this->number_of_elements; i++) {
		if (this->elements[i].first == e) {
			index = i;
			break;
		}
	}
	
	if (index == -1)
		return false;

	if (this->elements[index].second == 1) {
		for (int i = index; i < this->number_of_elements - 1; i++)
			this->elements[i] = this->elements[i + 1];

		this->elements[number_of_elements] = NULL_ELEMENTSPAIR;
		number_of_elements--;
	}
		
	else
		this->elements[index].second--;

	return true;
} // WC: theta(n); AC: theta(n); BC: theta(n); Total: theta(n) time complexity (where n <- number_of_elements)


bool SortedBag::search(TComp elem) const {
	bool element_found = false;

	for (int i = 0; i < this->number_of_elements; i++) {
		if (this->elements[i].first == elem) {
			element_found = true;
			break;
		}
	}

	return element_found;
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- number_of_elements)


int SortedBag::nrOccurrences(TComp elem) const {
	int index = -1;

	for (int i = 0; i < this->number_of_elements; i++) {
		if (this->elements[i].first == elem) {
			index = i;
			break;
		}
	}

	if (index != -1)
		return this->elements[index].second;

	return 0;
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- number_of_elements)


int SortedBag::size() const {
	int total_size = 0;

	for (int i = 0; i < this->number_of_elements; i++)
		total_size += this->elements[i].second;

	return total_size;
} // theta(n) time complexity (where n <- number_of_elements)


bool SortedBag::isEmpty() const {
	return this->number_of_elements == 0;
} // theta(1) time complexity


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
} // theta(1) time complexity


SortedBag::~SortedBag() {
	delete[] this->elements;
} // theta(1) time complexity
