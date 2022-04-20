#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

class SortedIndexedList {
private:
	friend class ListIterator;

private:
	struct DLLANode {
		TComp information;
		int previous;
		int next;

		DLLANode();

		DLLANode(TComp information, int previous, int next);
	};

	struct DLLA {
		DLLANode* list;
		int head, tail;
		int capacity, size;
		int first_empty;

		DLLA(); 

		DLLANode& operator[](int position); 
	};

	DLLA elements;
	Relation relation;
	int length;

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
