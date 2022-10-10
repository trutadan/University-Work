#include "lista.h"
#include <iostream>

using namespace std;


PNod creare_rec() {
    TElem x;
    cout << "x=";
    cin >> x;
    if (x == 0)
        return NULL;
    else {
        PNod p = new Nod();
        p->e = x;
        p->urm = creare_rec();
        return p;
    }
}

Lista creare() {
    Lista l;
    l._prim = creare_rec();
    return l;
}

void tipar_rec(PNod p) {
    if (p != NULL) {
        cout << p->e << " ";
        tipar_rec(p->urm);
    }
}

void tipar(Lista l) {
    tipar_rec(l._prim);
}

void distrug_rec(PNod p) {
    if (p != NULL) {
        distrug_rec(p->urm);
        delete p;
    }
}

void distruge(Lista l) {
    //se elibereaza memoria alocata nodurilor listei
    distrug_rec(l._prim);
}

/// the implementation of the requirements

// starting from a node, search if any of the next nodes are equal to the given value
bool recursivelySearchForElement(PNod node, TElem value) {
    if (node == NULL)
        return false;

    if (node->e == value)
        return true;

    return recursivelySearchForElement(node->urm, value);
}

// check if in the list, for each value, there is another node starting from the current one which has the same value
// the value is added only when the criteria above is met
PNod recursivelyTransformListInSet(PNod eachNodeFromList) {
    if (eachNodeFromList == NULL)
        return NULL;

    if (recursivelySearchForElement(eachNodeFromList->urm, eachNodeFromList->e))
        return recursivelyTransformListInSet(eachNodeFromList->urm);

    PNod starterNode = new Nod();
    starterNode->e = eachNodeFromList->e;
    starterNode->urm = recursivelyTransformListInSet(eachNodeFromList->urm);

    return starterNode;
}

// get the node of the recursively newly created set and assign it to the head of the set to be returned
Lista transformListInSet(Lista list) {
    Lista set;

    set._prim = recursivelyTransformListInSet(list._prim);

    return set;
}

// transform the second set into a set which contains only elements which are not in the first set, only in the second one
PNod recursivelyUniteTwoSets(Lista firstSet, PNod secondSetNode) {
    if (secondSetNode == NULL)
        return NULL;

    if (recursivelySearchForElement(firstSet._prim, secondSetNode->e))
        return recursivelyUniteTwoSets(firstSet, secondSetNode->urm);

    PNod starterNode = new Nod();
    starterNode->e = secondSetNode->e;
    starterNode->urm = recursivelyUniteTwoSets(firstSet, secondSetNode->urm);

    return starterNode;
}

// merge the node of the first set with the first node of the modified second set
Lista getUnionOfTwoSets(Lista firstSet, Lista secondSet) {
    PNod secondSetModified = recursivelyUniteTwoSets(firstSet, secondSet._prim);

    PNod firstSetIterator = firstSet._prim;
    while (firstSetIterator->urm != NULL)
        firstSetIterator = firstSetIterator->urm;

    firstSetIterator->urm = secondSetModified;

    return firstSet;
}
