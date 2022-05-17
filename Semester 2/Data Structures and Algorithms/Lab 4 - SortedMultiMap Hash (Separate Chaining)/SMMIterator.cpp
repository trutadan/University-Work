#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    // sll with all nodes of the table, ordered based on the relation
    // pros: easy to iterate through values
    // cons: hard to mantain after additions
    // improvement of this specific method: creating dll to make backward iteration faster

    this->current = nullptr;

    for (int index = 0; index < this->map.capacity; index++) {
        // current position of the table has no values(nodes)
        if (this->map.table[index] == nullptr)
            continue;

        SortedMultiMap::Node* previous_of_current = this->current;
        SortedMultiMap::Node* currently_iterated = this->map.table[index];
        SortedMultiMap::Node* head_of_new_list = nullptr;
        SortedMultiMap::Node* new_list = nullptr;

        while (this->current != nullptr && currently_iterated != nullptr) {
            SortedMultiMap::Node* new_node = new SortedMultiMap::Node;
            delete[] new_node->values;

            if (this->map.relation(this->current->key, currently_iterated->key)) {
                new_node->key = this->current->key;
                new_node->values = this->current->values;
                new_node->length = this->current->length;
                new_node->capacity = this->current->capacity;
                this->current = this->current->next;
            }

            else {
                new_node->key = currently_iterated->key;
                new_node->values = currently_iterated->values;
                new_node->length = currently_iterated->length;
                new_node->capacity = currently_iterated->capacity;
                currently_iterated = currently_iterated->next;
            }

            if (new_list == nullptr) {
                new_list = new_node;
                head_of_new_list = new_node;
            }

            else {
                new_list->next = new_node;
                new_list = new_list->next;
            }

        }

        while (this->current != nullptr) {
            SortedMultiMap::Node* new_node = new SortedMultiMap::Node;
            delete[] new_node->values;

            new_node->key = this->current->key;
            new_node->values = this->current->values;
            new_node->length = this->current->length;
            new_node->capacity = this->current->capacity;

            this->current = this->current->next;

            if (new_list == nullptr) {
                new_list = new_node;
                head_of_new_list = new_node;
            }

            else {
                new_list->next = new_node;
                new_list = new_list->next;
            }

        }

        while (currently_iterated != nullptr) {
            SortedMultiMap::Node* new_node = new SortedMultiMap::Node;
            delete[] new_node->values;

            new_node->key = currently_iterated->key;
            new_node->values = currently_iterated->values;
            new_node->length = currently_iterated->length;
            new_node->capacity = currently_iterated->capacity;

            currently_iterated = currently_iterated->next;

            if (new_list == nullptr) {
                new_list = new_node;
                head_of_new_list = new_node;
            }

            else {
                new_list->next = new_node;
                new_list = new_list->next;
            }

        }

        this->current = head_of_new_list;

        while (previous_of_current != nullptr) {
            SortedMultiMap::Node* next_node = previous_of_current->next;
            delete previous_of_current;
            
            previous_of_current = next_node;
        }

    }

    this->head = this->current;
    this->position = 0;
 } // Total: O(n*N) time complexity (where n<-number of different key-value pairs; N<-capacity of the table)

void SMMIterator::first(){
	this->current = this->head;
	this->position = 0;
} // theta(1)

void SMMIterator::next(){
	if (this->current == nullptr)
		throw std::exception();

	if (this->position + 1 == this->current->length) {
		this->current = this->current->next;
		this->position = 0;
	}

	else
		this->position++;
} // theta(1)

bool SMMIterator::valid() const{
	return this->current != nullptr;
} // theta(1)

TElem SMMIterator::getCurrent() const{
	if (this->current == nullptr)
		throw std::exception();

	return make_pair(this->current->key, this->current->values[this->position]);
} // theta(1)

SMMIterator::~SMMIterator() {
    while (this->head != nullptr) {
        SortedMultiMap::Node* next_node = this->head->next;
        delete this->head;

        this->head = next_node;
    }
} // Total: theta(n) time complexity (where n<-number of different keys pairs)