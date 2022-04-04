#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

//Node class suplimentary added
class Node
{

private:
	TComp data;
	Node* next;

public:
	Node(const TComp& data);

	TComp& getData();

	Node* getNext();

	void setNext(Node* value);
};

//SortedIndexedList already existed
class SortedIndexedList {

private:
	friend class ListIterator;

private:
	Node* first;
	int length;
	Relation relation;

public:
	SortedIndexedList(Relation r);

	int size() const;

	bool isEmpty() const;

	TComp getElement(int pos) const;

	void add(TComp e);

	TComp remove(int pos);

	int search(TComp e) const;

	ListIterator iterator();

	~SortedIndexedList();

};
