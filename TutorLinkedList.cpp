#include "TutorLinkedList.h"
#include "TutorStruct.h";

TutorLinkedList tutorLinkedList;
TutorStruct tt;

void searchL();
void sortDisplayL();
bool initializedL = false;

void initList() {
	if (initializedL == false) {
		tutorLinkedList.addDemoData(); //A bunch of records is added for presentation purposes
		initializedL = true;
	}
	system("cls");
	int lMenuChoice;
	cout << "Tutor Management System (Linked List Edition)\n";
	cout << "1. Add a Tutor\n";
	cout << "2. Display All Records\n";
	cout << "3. Search Menu\n";
	cout << "4. Sort and Display Data\n";
	cout << "5. Modify Record\n";
	cout << "6. Delete Record\n";
	cout << "7. Generate Available Tutors List\n";
	cout << "8. Exit\n";
	cout << "Enter your choice: ";
	cin >> lMenuChoice;
	tt.rejectChar();		//This function checks if the input is char and prompts for another int input
	system("cls");

	switch (lMenuChoice) {
	case 1:
		tutorLinkedList.addTutor();
		break;
	case 2:
		tutorLinkedList.display();
		break;
	case 3:
		searchL();
		break;
	case 4:
		sortDisplayL();
		break;
	case 5:
		tutorLinkedList.modifyRecord();
		break;
	case 6:
		tutorLinkedList.deleteRecord();
		break;
	case 7:
		tutorLinkedList.generateReport();
		break;
	case 8:
		exit(1);
	default:
		cout << "Invalid Entry!";
	}
	puts("");
	system("pause");
	initList();
}

void searchL() {
	system("cls");
	int choice;
	cout << "Search\n";
	cout << "1. Search by ID\n";
	cout << "2. Search by Rating\n";
	cout << "3. Search by Location\n";
	cout << "Enter your choice: ";
	cin >> choice;
	tt.rejectChar();
	switch (choice) {
	case 1:
		int id;
		cout << "Enter Tutor ID: ";
		cin >> id;
		tt.rejectChar();
		tutorLinkedList.searchByID(id);
		break;
	case 2:
		double rating;
		cout << "Enter Rating: ";
		cin >> rating;
		tt.rejectChar();
		tutorLinkedList.searchByRating(rating);
		break;
	case 3:
		tutorLinkedList.searchByLocation();
		break;
	default:
		cout << "Invalid Entry!";
		searchL();
	}
}

void sortDisplayL() {
	system("cls");
	int choice;
	cout << "Sort and Display\n";
	cout << "1. Sort by ID\n";
	cout << "2. Sort by Rating\n";
	cout << "3. Sort by Salary\n";
	cout << "Enter your choice: ";
	cin >> choice;
	tt.rejectChar();
	switch (choice) {
	case 1:
		tutorLinkedList.sortBy(choice);
		break;
	case 2:
		tutorLinkedList.sortBy(choice);
		break;
	case 3:
		tutorLinkedList.sortBy(choice);
		break;
	default:
		cout << "Invalid Entry!";
		sortDisplayL();
	}
}