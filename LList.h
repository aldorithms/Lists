#pragma once
#include "List.h"
#include "Link.h"
#include <assert.h>

// Linked list implementation
template <typename E> 
class LList : public List<E> 
{
private:
	Link<E>* head; // Pointer to list header
	Link<E>* tail; // Pointer to last element
	Link<E>* curr; // Access to current element
	int cnt; // Size of list
	void init() { // Intialization helper method
		curr = tail = head = new Link<E>;
		cnt = 0;
	}
	void removeall() { // Return link nodes to free store
		while (head != NULL) {
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	LList(int size = defaultSize) { init(); } // Constructor
	~LList() { removeall(); } // Destructor

	// 12. Clear list
	void clear() { removeall(); init(); } 
	// 1. Insert "it" at current position
	void insert(const E& it) {
		curr->next = new Link<E>(it, curr->next);
		if (tail == curr) tail = curr->next; // New tail
		cnt++;
	}
	// 2. Append "it" to list
	void append(const E& it) { 
		tail = tail->next = new Link<E>(it, NULL);
		cnt++;
	}
	// 3. Remove and return current element
	E remove() {
		assert(curr->next != NULL, "No element");
		E it = curr->next->element; // Remember value
		Link<E>* ltemp = curr->next; // Remember link node
		if (tail == curr->next) tail = curr; // Reset tail
		curr->next = curr->next->next; // Remove from list
		delete ltemp; // Reclaim space
		cnt--; // Decrement the count
		return it;
	}
	// 4. Place curr at list start
	void moveToStart() 
	{
		curr = head;
	}
	// 5. Place curr at list end
	void moveToEnd() 
	{
		curr = tail;
	}
	// 6. Move curr one step left; no change if already at front
	void prev() {
		if (curr == head)
			curr = tail; // No previous element
		Link<E>* temp = head;
		// March down list until we find the previous element
		while (temp->next != curr) temp = temp->next;
		curr = temp;
	}
	// 7. Move curr one step right; no change if already at end
	void next()
	{
		if (curr != tail)
			curr = curr->next;
		else if (curr == tail)
			curr = head;
	}
	// 8. Return length
	int length() const { return cnt; } 
	// 9. Return the position of the current element								   
	int currPos() const {
		Link<E>* temp = head;
		int i;
		for (i = 0; curr != temp; i++)
			temp = temp->next;
		return i;
	}
	// 10. Move down list to "pos" position
	void moveToPos(int pos) {
		assert((pos >= 0) && (pos <= cnt), "Position out of range");
		curr = head;
		for (int i = 0; i<pos; i++) curr = curr->next;
	}
	// 11. Return current element
	const E& getValue() const { 
		assert(curr->next != NULL, "No value");
		return curr->next->element;
	}

	// Print list contents
	void print()
	{	
		cout << " [ ";
		if (length() == 0)
			cout << "Empty";
		else
		{
			int currentPos = currPos();
			moveToStart();
			for (int i = 0; i < length(); i++)
			{
				if (i == currentPos)
					cout << "-> ";

				cout << getValue();

				if (i < length() - 1)
					cout << " | ";
				next();
			}
			moveToPos(currentPos);
			if (currentPos == length())
				cout << " | ->";
		}
		cout << " ]" << endl;
	}
};