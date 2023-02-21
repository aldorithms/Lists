/*
File name: Main.cpp
Project 1: Part 2 
Date: 10/26/18
*/

#include <iostream>
#include "AList.h"
#include "LList.h"
#include "Link.h"
#include "List.h"
using namespace std;

// Allow user to choose the type of List and type of Data
void userMenu(AList<int>&, AList<double>&, AList<char>&,
	LList<int>&, LList<double>&, LList<char>&);
// Input data
template <typename E>
void inputData(List<E>&, E);
// Output the list and command options
template <typename E>
void optionsMenu(List<E>&, int, int);
// Input the selected option
template <typename E>
void optionsSelect(List<E>&, bool&);
// Display all the lists
void displayExistLists(AList<int>&, AList<double>&, AList<char>&,
	LList<int>&, LList<double>&, LList<char>&);

//---------------------------- MAIN --------------------------------------------
int main()
{
	AList<int> AL1(100);
	AList<double> AL2(100);
	AList<char> AL3(100);

	LList<int> LL1(100);
	LList<double> LL2(100);
	LList<char> LL3(100);

	char check;
	bool inProgram = true;
	while (inProgram == true)
	{
		userMenu(AL1, AL2, AL3, LL1, LL2, LL3); // Main program run within this function
		cout << "\nProgram Options:\n  (A) Continue.\n  (B) Reset All Data.\n  (C) Exit.\n";
		while (true)
		{
			cout << "\n>> ";
			cin >> check;

			if (check == 'A' || check == 'a') // Continue the program and save all the input data
			{
				system("CLS");
				break;
			}
			else if (check == 'B' || check == 'b') // Restart the program and delete all the data and the memory allocated
			{
				AL1.~AList();
				AL2.~AList();
				AL3.~AList();
				LL1.~LList();
				LL2.~LList();
				LL3.~LList();
				system("CLS");
				return main();
			}
			else if (check == 'C' || check == 'c') // Terminate the program
			{
				inProgram = false;
				break;
			}
			else // Invalid Inputs
				cout << "\n[----> Invalid Response! <----]\n\n A / B / C\n" << endl;
		}
	}

	return 0;
}
//-----------------------------------------------------------------------------

// Allow user to choose the type of List and type of Data
void userMenu(AList<int> &a1, AList<double> &a2, AList<char> &a3,
	LList<int> &l1, LList<double> &l2, LList<char> &l3)
{
	displayExistLists(a1, a2, a3, l1, l2, l3); // Display the all lists with and/or without values
		
	int listType = 0;
	cout << "\nChoose the list implementation:\n1. Array-Based List\n2. Linked List\n\n>> ";
	cin >> listType;
	if (listType != 1 && listType != 2)
	{
		cout << "\n[----> Invalid Input! <----]\n" << endl;
	}
	else
	{
		int dataType = 0;
		cout << "\nChoose the data type:\n1. int\n2. double\n3. char\n\n>> ";
		cin >> dataType;

		if (dataType == 1) // Int. data type
		{
			cout << "\nEnter the list (-1 to continue):\n(Format Example: 1,2,3,...,-1)\n";
			int a = 0;
			if (listType == 1)
			{
				inputData(a1, a);
				optionsMenu(a1, listType, dataType);
			}
			else
			{
				inputData(l1, a);
				optionsMenu(l1, listType, dataType);
			}
		}
		else if (dataType == 2) // Double. data type
		{
			cout << "\nEnter the list (-1 to continue):\n(Format Example: 1.1,2.1,3.1,...,-1)\n";
			double b = 0;
			if (listType == 1)
			{
				inputData(a2, b);
				optionsMenu(a2, listType, dataType);
			}
			else
			{
				inputData(l2, b);
				optionsMenu(l2, listType, dataType);
			}
		}
		else if (dataType == 3) // Char. data type
		{
			cout << "\nEnter the list (Enter: . to continue):\n(Format Example: a,b,c,...,.)\n";
			char c = '0';
			if (listType == 1)
			{
				inputData(a3, c);
				optionsMenu(a3, listType, dataType);
			}
			else
			{
				inputData(l3, c);
				optionsMenu(l3, listType, dataType);
			}
		}
		else
		{
			cout << "\n[----> Invalid Data Type! <----]\n" << endl;
		}
	}
}
// Input data
template <typename E>
void inputData(List<E> &a, E input)
{
	if (a.length() == 0) // Run input if the list is empty
	{
		cout << "\n>> ";
		while (true)
		{
			cin >> input;
			if (input != -1 && input != '.')
			{
				a.append(input);
			}
			else
				break;
			cin.ignore(1); // Ignore the commas
		}
	}
}
// Output the list and command options 
template <typename E>
void optionsMenu(List<E> &a, int x, int y)
{
	bool endOption = false;
	while (endOption == false)
	{
		if (x == 1 && y == 1)
			cout << "\n A-List <int>:    ";
		else if (x == 1 && y == 2)
			cout << "\n A-List <double>: ";
		else if (x == 1 && y == 3)
			cout << "\n A-List <char>:   ";
		else if (x == 2 && y == 1)
			cout << "\n L-List <int>:    ";
		else if (x == 2 && y == 2)
			cout << "\n L-List <double>: ";
		else if (x == 2 && y == 3)
			cout << "\n L-List <char>:   ";
		a.print();

		cout << "\nFunctions:\n 1. Insert an element at current position."
			<< "\n 2. Append an element."
			<< "\n 3. Remove and return the current element."
			<< "\n 4. Reset position to the top of lthe list."
			<< "\n 5. Set position to the end of the list."
			<< "\n 6. Previous position."
			<< "\n 7. Next position."
			<< "\n 8. List size."
			<< "\n 9. Current position."
			<< "\n 10. Move to a position."
			<< "\n 11. Current Element."
			<< "\n 12. Clear the list."
			<< "\n 0. Exit." << endl;
		optionsSelect(a, endOption);
	}
}
// Input the selected option
template <typename E>
void optionsSelect(List<E> &a, bool &endOption)
{
	int x = 0;

	cout << "\n>> ";
	cin >> x;

	E element;
	int pos;

	switch (x)
	{
	case 1: cout << "\nInserting >> ";
		cin >> element;
		a.insert(element);
		break;
	case 2: cout << "\nAppending >> ";
		cin >> element;
		a.append(element);
		break;
	case 3: cout << "\nRemoving: " << a.remove() << endl;
		break;
	case 4: a.moveToStart();
		break;
	case 5: a.moveToEnd();
		break;
	case 6: a.prev();
		break;
	case 7: a.next();
		break;
	case 8: cout << "\nList size: " << a.length() << endl;
		break;
	case 9: cout << "\nCurrent Position: " << a.currPos() << endl;
		break;
	case 10: cout << "\nMove to position >> ";
		cin >> pos;
		a.moveToPos(pos);
		break;
	case 11: cout << "\nCurrent Element: " << a.getValue() << endl;
		break;
	case 12: cout << "\nThe list has been cleared!" << endl;
		a.clear();
		break;
	default: endOption = true;
		break;
	}
	cout << endl;
}
// Display all the lists
void displayExistLists(AList<int> &a1, AList<double> &a2, AList<char> &a3,
	LList<int> &l1, LList<double> &l2, LList<char> &l3)
{
	cout << "\n(1,1) A-List <int>:    ";
	a1.print();
	cout << "\n(1,2) A-List <double>: ";
	a2.print();
	cout << "\n(1,3) A-List <char>:   ";
	a3.print();
	cout << "\n(2,1) L-List <int>:    ";
	l1.print();
	cout << "\n(2,2) L-List <double>: ";
	l2.print();
	cout << "\n(2,3) L-List <char>:   ";
	l3.print();
}
