#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

// Collision resolution by chaining: each slot from the hash table
// contains a linked list, with the elements that hash to that slot
class SortedMultiMap {
	friend class SMMIterator;

    private:
        struct Node {
            int key;
            TValue* values;
            int length, capacity;
            Node* next;

            Node();
        };

        Node** nodes;
        int length, capacity;
        double load_factor;
        Relation relation;

    public:

    SortedMultiMap(Relation r);

    int hash_function(int key) const;

    void add(TKey c, TValue v);

    vector<TValue> search(TKey c) const;

    bool remove(TKey c, TValue v);

    int size() const;

    bool isEmpty() const;

    SMMIterator iterator() const;

    ~SortedMultiMap();
};
