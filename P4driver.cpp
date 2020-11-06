//bintreedr.cpp
//copyright by Kayla Fox
//student ID: 0717

#include "bintree.h"
#include "string"
#include <iostream>
#include <cstdlib>

using namespace std;

BinaryTreeNode<int>* root_ptr = NULL;


int main()
{
	// Pre: None.
	// Post: Give the user a menu of choices.
	//       Based on what command the user inputs, take
	//       the appropriate action as guaranteed by the menu.
	//       Input is accepted in a case-insensitive manner!

	char command, i;
	float value;
	void printmenu();

	printmenu();
	do
	{
		cin >> command;
		switch (command)
		{
		case 'I':
		case 'i':
			cin >> i;
			insert<int>(root_ptr, i);
			break;
		case 'D':
		case 'd':
			cin >> i;
			// remove<int>(root_ptr, i);
			break;
		case 'C':
		case 'c':
			tree_clear<int>(root_ptr);
			break;
		case 'R':
		case 'r':
			// reflect<int>(root_ptr);
			break;
		case 'P':
		case 'p':
			cin >> i;
			printTree(root_ptr);
			break;
		case 'TR':
		case 'tr':
			cin >> i;
			preorder(i, root_ptr);
			break;
		case 'TI':
		case 'ti':
			cin >> i;
			inorder(i, root_ptr);
			break;
		case 'TO':
		case 'to':
			cin >> i;
			postorder(i, root_ptr);
			break;
		case 'Q':
		case 'q':
			cin >> i;
			break;
		};
	} while ((command != 'Q') && (command != 'q'));
};

void printmenu()
{
	// Pre: None.
	// Post: Print a menu of choices.

	cout << "Available commands : " << endl;
	cout << "I : to insert the specified data value into the BST" << endl;
	cout << "D : to delete the item with the specified data value from the BST" << endl;
	cout << "C : to clear the tree," << endl;
	cout << "R : to reflect" << endl;
	cout << "P : to print the entire tree sideways" << endl;
	cout << "TR : to traverse in preorder and print values" << endl;
	cout << "TI : to traverse in inorder and print values" << endl;
	cout << "TO : to Traverse in pOstorder and print values" << endl;
	cout << "Q :  to quit" << endl;
};
