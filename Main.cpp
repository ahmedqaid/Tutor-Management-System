#include <iostream>
using namespace std;

void initList();
void initArray();

int main() {
	system("cls");
	int systemChoice;
	cout << "Tutor Management System" << endl;
	cout << "\xB2 eXcel Tuition Centre \xB2" << endl;
	cout << "-----------------------------" << endl;
	cout << "1. TMS (Linked List Edition)" << endl;
	cout << "2. TMS (Array Edition)" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter you choice: ";
	cin >> systemChoice;

	if (cin.fail()) {			//This if-statement checks if the input for int is char, and clear the cin memory
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	else if (systemChoice == 1) {
		initList();			   //Based on the choice, the linked list system will be initiated
	}
	else if (systemChoice == 2) {
		initArray();		   //Based on the choice, the array system will be initiated
	}
	else if (systemChoice == 3) {
		exit(1);
	}
	else {
		cout << "Invalid Choice!";
	}
	main();
}