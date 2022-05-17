#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::Node::Node()
{
	this->key = 0;
	this->length = 0;
	this->capacity = 1;
	this->values = new TValue[this->capacity];
	this->next = nullptr;
} // theta(1)

SortedMultiMap::SortedMultiMap(Relation r) {
	this->length = 0;
	this->capacity = 1;

	// if the load factor of the table after an insertion is greater than 
	// or equal to 0.7, we double the size of the table
	this->load_factor = 0.7;

	this->table = new Node*[this->capacity];
	for (int index = 0; index < this->capacity; index++)
		this->table[index] = nullptr;

	this->relation = r;
} // theta(1)

int SortedMultiMap::hashKey(int key) const
{
	if (key < 0)
		key = this->capacity + key % this->capacity;

	return key % this->capacity;
} // theta(1)

void SortedMultiMap::add(TKey c, TValue v) {
	int position = this->hashKey(c);

	Node* each_node = this->table[position];
	Node* previous_node = nullptr;

	while (each_node != nullptr) {
		if (each_node->key == c) {

			// resize the vector of values from the current node
			if (each_node->capacity == each_node->length) {
				each_node->capacity *= 2;
				TValue* auxiliar_pointer = new TValue[each_node->capacity];

				for (int index = 0; index < each_node->length; index++)
					auxiliar_pointer[index] = each_node->values[index];

				delete[] each_node->values;
				each_node->values = auxiliar_pointer;
			}

			// add the new value to the end of the dynamic array
			each_node->values[each_node->length] = v;
			each_node->length++;
			this->length++;
			break;
		}

		// if the key is not in the singly linked list for this position in the table, 
		// keep track of the position of the node where it should be added
		if (each_node->key != c && !this->relation(c, each_node->key))
			previous_node = each_node;

		each_node = each_node->next;
	}
	
	// not any node with the searched key was found 
	if (each_node == nullptr) {

		// resize the whole hashtable
		if (this->load_factor <= double(this->length + 1) / this->capacity) {

			this->capacity *= 2;
			Node** auxiliar_pointer = new Node* [this->capacity];

			for (int index = 0; index < this->capacity; index++)
				auxiliar_pointer[index] = nullptr;

			for (int index = 0; index < this->capacity / 2; index++) {
				Node* current_node = this->table[index];

				while (current_node != nullptr) {
					int auxiliar_position = this->hashKey(current_node->key);
					Node* next = current_node->next;
					current_node->next = auxiliar_pointer[auxiliar_position];
					auxiliar_pointer[auxiliar_position] = current_node;
					current_node = next;
				}
			}

			delete[] this->table;
			this->table = auxiliar_pointer;

			// recalculates the hash for the key to be added after resizing the table
			position = this->hashKey(c);
		}

		// create a new node with the corresponding data
		Node* new_node = new Node;

		new_node->length = 1;
		new_node->key = c;
		new_node->values[0] = v;

		// the node should be added first
		if (previous_node == nullptr) {
			new_node->next = this->table[position];
			this->table[position] = new_node;
		}

		// any other position in the singly linked list, except first 
		else {
			new_node->next = previous_node->next;
			previous_node->next = new_node;
		}

		this->length++;
	}
}  // WC: theta(n); AC: theta(1); BC: theta(1); Total: O(n) time complexity (where n<-number of values with key=c)

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> searched_values;

	int position = this->hashKey(c);
	// take the sll corresponding to the key provided
	Node* each_node = this->table[position];

	// iterate through sll and find the nodes with the key searched
	while (each_node != nullptr) {
		if (each_node->key == c) {
			for (int index = 0; index < each_node->length; index++)
				searched_values.push_back(each_node->values[index]);
			
			break;
		}

		each_node = each_node->next;
	}

	return searched_values;
} // Total: theta(n) time complexity (where n<-number of values with key=c)

bool SortedMultiMap::remove(TKey c, TValue v) {
	int position = this->hashKey(c);

	Node* each_node = this->table[position];
	Node* previous_node = nullptr;

	while (each_node != nullptr) {
		// we found the node with the given key in the corresponding singly linked list from the hash table
		if (each_node->key == c) {
			bool removal_status = false;

			for (int index = 0; index < each_node->length; index++)
				// we found the value for which we're searching, for the corresponding key
				if (each_node->values[index] == v) {
					// move all values one position back over the removed value
					for (int auxiliar_index = index; auxiliar_index + 1 < each_node->length; auxiliar_index++)
						each_node->values[auxiliar_index] = each_node->values[auxiliar_index + 1];

					each_node->length--;
					this->length--;
					removal_status = true;
					break;
				}

			// if the node has no more values
			if (each_node->length == 0) {
				delete[] each_node->values;

				// remove it if it is the first in the list
				if (previous_node == nullptr) {
					this->table[position] = each_node->next;
					delete each_node;
				}

				// move the next node on the current one and delete the current one
				else {
					Node* next_node = each_node->next;
					previous_node->next = next_node;
					delete each_node;
				}

			}
			return removal_status;
		}

		// iterate through all the nodes
		previous_node = each_node;
		each_node = each_node->next;
	}

	// there is no node for the given position
	return false;
} //  WC: theta(n); AC: theta(1); BC: theta(1); Total: O(n) time complexity (where n<-number of different keys pairs)

int SortedMultiMap::size() const {
	return this->length;
} // theta(1)

bool SortedMultiMap::isEmpty() const {
	return this->length == 0;
} // theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
} // Total: O(n*N) time complexity (where n<-number of different key-value pairs; N<-capacity of the table)

SortedMultiMap::~SortedMultiMap() {
	for (int index = 0; index < this->capacity; index++) {

		Node* each_node = this->table[index];
		Node* next_node = this->table[index];
		
		while (each_node != nullptr) {
			// delete all the values from each node
			delete[] each_node->values;

			// delete all nodes from each position in the hashtable
			next_node = next_node->next;
			delete each_node;

			each_node = next_node;
		}
	}

	// delete the pointer of the hashtable
	delete[] this->table;
} // theta(n)
