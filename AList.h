#pragma once
#include "List.h"
#include "Link.h"
#include <assert.h>

// Array-based list implementation
template <typename E> 
class AList : public List<E> 
{
private:
	int maxSize; // Maximum size of list
	int listSize; // Number of list items now
	int curr; // Position of current element
	E* listArray; // Array holding list elements
public:
	AList(int size = defaultSize) { // Constructor
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}
	~AList() { delete[] listArray; } // Destructor

	// 12. Reinitialize the list
	void clear() { 
		delete[] listArray; // Remove the array
		listSize = curr = 0; // Reset the size
		listArray = new E[maxSize]; // Recreate array
	}
	// 1. Insert "it" at current position
	void insert(const E& it) {
		assert(listSize < maxSize, "List capacity exceeded");
		for (int i = listSize; i>curr; i--) // Shift elements up
			listArray[i] = listArray[i - 1]; // to make room
		listArray[curr] = it;
		listSize++; // Increment list size
	}
	// 2. Append "it"
	void append(const E& it) { 
		assert(listSize < maxSize, "List capacity exceeded");
		listArray[listSize++] = it;
	}
	// 3. Remove and return the current element.
	E remove() {
		assert((curr >= 0) && (curr < listSize), "No element");
		E it = listArray[curr]; // Copy the element
		for (int i = curr; i<listSize - 1; i++) // Shift them down
			listArray[i] = listArray[i + 1];
		listSize--; // Decrement size
		return it;
	}
	// 4. Reset position
	void moveToStart() { 
		curr = 0; 
	} 
	// 5. Set at end
	void moveToEnd() { 
		curr = listSize;
	}
	// 6. Back up
	void prev() { 
		if (curr != 0) curr--; 
	}
	// 7. Next
	void next() { 
		if (curr < listSize) curr++; 
	} 
	// 8. Return list size											 
	int length() const { return listSize; }
	// 9. Return current position
	int currPos() const { return curr; }
	// 10. Set current list position to "pos"
	void moveToPos(int pos) {
		assert((pos >= 0) && (pos <= listSize), "Pos out of range");
		curr = pos;
	}
	// 11. Return current element
	const E& getValue() const { 
		assert((curr >= 0) && (curr<listSize), "No current element");
		return listArray[curr];
	}

	// Print list contents
	void print() {
		cout << " [ ";
		if (listSize == 0)
			cout << "Empty";
		else
		{
			for (int i = 0; i < listSize; i++)
			{
				if (i == curr)
					cout << "-> ";

				cout << listArray[i];

				if (i < listSize - 1)
					cout << " | ";
			}
			if (listSize == curr)
				cout << " | ->";
		}
		cout << " ]" << endl;
	}
};