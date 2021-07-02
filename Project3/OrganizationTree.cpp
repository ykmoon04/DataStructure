#include <iostream>
#include "tree.h"
using namespace std;

int main() {
	HierarchyTree org;
	string ceo;
	
	string cmd;

	while (true) {
		if (org.isEmpty()) {
			cout << "Hire CEO: ";
			cin >> ceo;
			org.hire("", ceo);
		}
		else {
			cout << "Commands (Exit - Q): ";
			cin >> cmd;
			if (cmd == "Fire" || cmd == "fire") {
				string target;
				cin >> target;
				org.fire(target);
			}
			else if (cmd == "Print" || cmd == "print") {
				org.print();
			}
			else if (cmd == "Q" || cmd == "q") {
				break;
			}
			else {
				string temp, sub;
				cin >> temp >> sub;
				org.hire(cmd, sub);
			}
		}
	}

	system("pause");
}