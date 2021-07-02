//--------------------------------------------------------------------
//
//  Laboratory 5                                           test5.cpp
//
//  Test program for the operations in the Stack ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include "stackarr.cpp"
//#include "stackdwn.cpp"

//--------------------------------------------------------------------

void main()
{
	Stack<char> testStack(8);     // Test stack
	char testElement;             // Stack element
	char cmd;                     // Input command

	cout << endl << "Commands:" << endl;
	cout << "  +x : Push x" << endl;
	cout << "  -  : Pop" << endl;
	cout << "  C  : Clear" << endl;
	cout << "  E  : Empty stack?" << endl;
	cout << "  F  : Full stack?" << endl;
	cout << "  Q  : Quit the test program" << endl;
	cout << endl;

	do
	{
		testStack.showStructure();                    // Output stack

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		if (cmd == '+')
			cin >> testElement;

		switch (cmd)
		{
		case '+':                                  // push
			cout << "Push " << testElement << endl;
			testStack.push(testElement);
			break;

		case '-':                                  // pop
			cout << "Popped " << testStack.pop() << endl;
			break;

		case 'C': case 'c':                       // clear
			cout << "Clear the stack" << endl;
			testStack.clear();
			break;

		case 'E': case 'e':                       // empty
			if (testStack.isEmpty())
				cout << "Stack is empty" << endl;
			else
				cout << "Stack is NOT empty" << endl;
			break;

		case 'F': case 'f':                       // full
			if (testStack.isFull())
				cout << "Stack is full" << endl;
			else
				cout << "Stack is NOT full" << endl;
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
		}
	} while (cmd != 'Q'  &&  cmd != 'q');

}
