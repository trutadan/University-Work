#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

//Node functionalities

Node::Node(const TComp& _data)
{
	this->data = _data;
	this->next = nullptr;
} // theta(1) time complexity

TComp& Node::getData()
{
	return this->data;
} // theta(1) time complexity

Node* Node::getNext()
{
	return this->next;
} // theta(1) time complexity

void Node::setNext(Node* value)
{
	this->next = value;
} // theta(1) time complexity

//SortedIndexedList functionalities

SortedIndexedList::SortedIndexedList(Relation r) {
	this->length = 0;
	this->relation = r;
	this->first = nullptr;
} // theta(1) time complexity

int SortedIndexedList::size() const {
	return this->length;
} // theta(1) time complexity

bool SortedIndexedList::isEmpty() const {
	return (this->length==0);
} // theta(1) time complexity

TComp SortedIndexedList::getElement(int i) const{
	if (i >= length || i < 0)
		throw exception();

	Node* starting_node = this->first;

	while (i > 0) {
		starting_node = starting_node->getNext();
		i--;
	}

	return starting_node->getData();
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)

TComp SortedIndexedList::remove(int i) {
	if (i > length || i < 0)
		throw exception();

	if (this->length == 0)
		throw exception();

	this->length--;

	TComp removed_tcomp = NULL_TCOMP;

	if (i == 0) {
		removed_tcomp = this->first->getData();
		this->first = this->first->getNext();
	}

	else {
		Node* current = this->first;

		int index = 0;
		while (index != i-1) {
			current = current->getNext();
			index++;
		}

		removed_tcomp = current->getNext()->getData();
		current->setNext(current->getNext()->getNext());

	}

	return removed_tcomp;
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)

int SortedIndexedList::search(TComp e) const {
	if (this->length == 0)
		return -1;

	int index = 0;

	Node* starting_node = this->first;
	do {
		if (e == starting_node->getData())
			return index;

		if (this->relation(e, starting_node->getData()))
			return -1;

		starting_node = starting_node->getNext();
		index++;

	} while (starting_node != nullptr);

	return -1;
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)

void SortedIndexedList::add(TComp e) {
	Node* node_to_be_added = new Node{ e };
	this->length++;

	if (this->first == nullptr) {
		this->first = node_to_be_added;
		return;
	}

	Node* current = this->first;

	while (current->getNext() != NULL && !this->relation(node_to_be_added->getData(), current->getNext()->getData())) {
		current = current->getNext();
	}

	if (current == this->first && this->relation(node_to_be_added->getData(), current->getData())){
		node_to_be_added->setNext(current);
		this->first = node_to_be_added;
	}

	else {
		node_to_be_added->setNext(current->getNext());
		current->setNext(node_to_be_added);
	} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
} // theta(1) time complexity

SortedIndexedList::~SortedIndexedList() {
	Node* starting_node = this->first;

	while (starting_node != nullptr) {
		Node* auxiliary_node = starting_node;
		starting_node = starting_node->getNext();

		delete auxiliary_node;
	}
} // theta(n) time complexity (where n <- length)
