#include <iostream>
#include <string>
#include "addressBook.h"

using namespace std;

void print_help() {
	cout << "R : read from a file" << endl;
	cout << "+ :  add a new entry" << endl;
	cout << "- : remove an entry" << endl;
	cout << "W : write to a file" << endl;
	cout << "M : select a month" << endl;
	cout << "Q : quit the program" << endl;
	cout << endl;
}

int main() {

	print_help();

	char cmd;
	string name, number, birth, fileName;
	string* s = new string[3];
	List myBook;

	do {
		cout << endl;
		cout << "Command >> ";
		cin >> cmd;
		cin.get();

		switch(cmd) {

		case 'R': case 'r':		
			cout << "Enter the name of the file : ";
			getline(cin, fileName);
			myBook.readFile(fileName);
			myBook.summary();
			break;

		case '+':		
			cout << "Add an entry" << endl;
			cout << "Name : ";
			getline(cin, name);
			cout << "Phone : ";
			getline(cin, number);
			cout << "Birthday : ";
			getline(cin, birth);
			s[0] = name; s[1] = number; s[2] = birth;
			myBook.insert(s);
			myBook.summary();
			break;

		case '-':		
			cout << "Remove an entry" << endl;
			cout << "Name : ";
			getline(cin, name);
			myBook.remove(name);
			myBook.summary();
			break;

		case 'W': case 'w':		
			cout << "Enter the name of the file : ";
			getline(cin, fileName);
			myBook.writeList(fileName);
			cout << "The list is written into " << fileName << endl;
			break;

		case 'M': case 'm':		
			cout << "Enter the selected month : ";
			getline(cin, birth);
			myBook.countBirth(birth);
			break;		

		case 'Q': case 'q':		
			cout << "Quit the program" << endl;
			break;

		default:
			cout << "Invalid Command" << endl;
			break;
		}
		
	} while (cmd != 'Q' && cmd != 'q');


	return 0;
}