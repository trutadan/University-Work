#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::DLLANode::DLLANode() : information(NULL_TCOMP), previous(0), next(0)
{
} // theta(1)

SortedIndexedList::DLLANode::DLLANode(TComp information, int previous, int next) : information { std::move(information) }, previous{ previous }, next{ next }
{
} // theta(1)

SortedIndexedList::DLLA::DLLA()
{
	this->capacity = 1;
	this->size = 1;
	this->list = new DLLANode[this->capacity];
	this->list[0] = DLLANode(NULL_TCOMP, -1, -1);
	this->first_empty = 0;
	this->head = -1;
	this->tail = -1;
} // theta(1)

SortedIndexedList::DLLANode &SortedIndexedList::DLLA::operator[](int position)
{
	return this->list[position];
} // theta(1)

SortedIndexedList::SortedIndexedList(Relation r) {
	this->relation = r;
	this->length = 0;
} // theta(1)

int SortedIndexedList::size() const {
	return this->length;
} // theta(1)

bool SortedIndexedList::isEmpty() const {
	return this->length == 0;
} // theta(1)

TComp SortedIndexedList::getElement(int i) const{
    DLLA elements = this->elements;

	if (i >= length || i < 0)
		throw exception();

    int pos = elements.head;
    for (int node = elements.head; i >= 0; node = elements[node].next) {
        pos = node;
        i--;
    }

    return elements[pos].information;
} // theta(1)

TComp SortedIndexedList::remove(int i) {
    if (i > length || i < 0)
        throw exception();

    if (this->length == 0)
        throw exception();

    DLLA& elements = this->elements;
    TComp removed_tcomp = NULL_TCOMP;

    // remove the single existing element from the list
    if (this->length == 1) {
        removed_tcomp = elements[elements.head].information;

        elements[elements.head].next = elements.first_empty;
        elements.first_empty = elements.head;
        elements.head = elements.tail = -1;

        this->length--;

        return removed_tcomp;
    }

    // remove the first element from the list
    if (i == 0) {
        removed_tcomp = elements[elements.head].information;
        int copy_new_head = elements[elements.head].next;

        elements[elements.head].next = elements.first_empty;
        elements.first_empty = elements.head;
        elements.head = copy_new_head;
        elements[elements.head].previous = -1;

        this->length--;

        return removed_tcomp;
    }

    // remove the last element from the list
    if (i == this->length) {
        removed_tcomp = elements[elements.tail].information;
        int copy_new_tail = elements[elements.tail].previous;

        elements[elements.tail].next = elements.first_empty;
        elements.first_empty = elements.tail;
        elements.tail = copy_new_tail;
        elements[elements.tail].next = -1;

        this->length--;

        return removed_tcomp;
    }

    // go to the node from the position we need to remove
    int pos;
    for (int node = elements.head; i >= 0; node = elements[node].next) {
        pos = node;
        i--;
    }
     
    // remove the element between two existing elements
    removed_tcomp = elements[pos].information;

    elements[elements[pos].previous].next = elements[pos].next;
    elements[elements[pos].next].previous = elements[pos].previous;
    elements[pos].next = elements.first_empty;
    elements.first_empty = pos;

    this->length--;

    return removed_tcomp;
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)

int SortedIndexedList::search(TComp e) const {
    if (this->length == 0)
        return -1;

    int index = 0;
    for (int node = this->elements.head; node != -1; node = this->elements.list[node].next){
        if (this->elements.list[node].information == e)
            return index;

        else if (!relation(this->elements.list[node].information, e))
            break;

        index++;
    }

	return -1;
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)

void SortedIndexedList::add(TComp e) {
    DLLA& elements = this->elements;

    // resize list
    if (elements.size == elements.capacity && elements.first_empty == -1) {
        elements.capacity *= 2;
        auto* aux = new DLLANode[elements.capacity];
        
        for (int i = 0; i < elements.size; ++i)
            aux[i] = elements[i];
        
        delete[] elements.list;
        
        elements.list = aux;
    }

    // a new element has been added so the first_empty position should be modified
    if (elements.first_empty == -1) {
        elements.first_empty = elements.size;
        elements[elements.first_empty] = DLLANode(NULL_TCOMP, -1, -1);
        elements.size++;
    }

    // the list is empty
    if (this->length == 0) {
        int copy_empty = elements.first_empty;
        
        elements.first_empty = elements[elements.first_empty].next;
        elements[copy_empty] = DLLANode(e, -1, -1);
        
        elements.tail = elements.head = copy_empty;
        this->length++;
        
        return;
    }

    int copy_empty = elements.first_empty;
    elements.first_empty = elements[elements.first_empty].next;
	
    // place the new element in the first position
    if (relation(e, elements[elements.head].information)) {
        elements[copy_empty] = DLLANode(e, -1, elements.head);
        
        elements[elements.head].previous = copy_empty;
        elements.head = copy_empty;
        this->length++;

        return;
    }
    
    // place the new element in the last position
    if (relation(elements[elements.tail].information, e)) {
        elements[copy_empty] = DLLANode(e, elements.tail, -1);
        
        elements[elements.tail].next = copy_empty;
        elements.tail = copy_empty;
        this->length++;

        return;
    }
    
    // find the position where the new element should be placed
    int after = elements.head;
    for (int node = elements.head; true; node = elements[node].next) 
        if (relation(elements[node].information, e) && elements[node].information != e)
            after = node;
        else 
            break;
    
    // place the new element between two existing elements
    elements[copy_empty] = DLLANode(e, after, elements[after].next);
    elements[elements[after].next].previous = copy_empty;
    elements[after].next = copy_empty;

    this->length++;
} // WC: theta(n); AC: theta(n); BC: theta(1); Total: O(n) time complexity (where n <- length)

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
} // theta(1)

//destructor
SortedIndexedList::~SortedIndexedList() {
	delete[] elements.list;
} // theta(1)

 
