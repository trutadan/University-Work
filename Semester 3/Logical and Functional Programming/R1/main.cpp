#include "lista.h"
#include <iostream>

// 1. a. Transform a list in a set.
// b. Determine the union of two sets. The sets are represented as lists.

int main()
{
	{
		// test the first requirement
		std::cout << "Enter the list:\n";
		Lista list;
		list = creare();

		std::cout << "The list transformed into a set:\n";
		Lista setFromList = transformListInSet(list);
		tipar(setFromList);

		// test the second requirement
		std::cout << "\nEnter first set:\n";
		Lista firstSet;
		firstSet = creare();

		std::cout << "Enter second set:\n";
		Lista secondSet;
		secondSet = creare();

		Lista firstSetUnitedWithSecond = getUnionOfTwoSets(firstSet, secondSet);

		std::cout << "The union of the two sets:\n";
		tipar(firstSetUnitedWithSecond);

		distruge(list);
		distruge(setFromList);
		distruge(firstSet);
		distruge(secondSet);
	}

	_CrtDumpMemoryLeaks();	
}
