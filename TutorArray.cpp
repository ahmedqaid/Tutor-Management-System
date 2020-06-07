#include "TutorArray.h"
#include "TutorStruct.h"

TutorArray tutorArray;
TutorStruct t;

void searchA();
void sortDisplayA();
bool initializedA = false;

void initArray() {
	if (initializedA == false) {
		tutorArray.addDemoData(); //Adds demo records in array system for presentation purposes
		initializedA = true;
	}
	system("cls");
	int lMenuChoice;
	cout << "Tutor Management System (Array of Structure Edition)\n";
	cout << "1. Add a Tutor\n";
	cout << "2. Display All Records\n";
	cout << "3. Search Menu\n";
	cout << "4. Sort and Display Data\n";
	cout << "5. Modify Record\n";
	cout << "6. Delete Record\n";
	cout << "7. Generate Available Tutors List\n";
	cout << "8. View Records\n";
	cout << "9. Exit\n";
	cout << "Enter your choice: ";
	cin >> lMenuChoice;
	t.rejectChar();
	system("cls");

	switch (lMenuChoice) {
	case 1:
		tutorArray.addTutor();
		break;
	case 2:
		tutorArray.display();
		break;
	case 3:
		searchA();
		break;
	case 4:
		sortDisplayA();
		break;
	case 5:
		tutorArray.modifyRecord();
		break;
	case 6:
		tutorArray.deleteRecord();
		break;
	case 7:
		tutorArray.generateReport(); //This is the report that shows the available vacancy for new tutors
		break;
	case 8:
		tutorArray.view();
		break;
	case 9:
		exit(1);
	default:
		cout << "Invalid Entry!";
	}
	puts("");
	system("pause");
	initArray();
}

void searchA() {
	system("cls");
	int choice;
	cout << "Search\n";
	cout << "1. Search by ID\n";
	cout << "2. Search by Rating\n";
	cout << "3. Search by Location\n";
	cout << "Enter your choice: ";
	cin >> choice;
	t.rejectChar();
	switch (choice) {
	case 1:
		int id;
		cout << "Enter Tutor ID: ";
		cin >> id;
		t.rejectChar();
		tutorArray.searchByID(id);
		break;
	case 2:
		double rating;
		cout << "Enter Rating: ";
		cin >> rating;
		t.rejectChar();
		tutorArray.searchByRating(rating);
		break;
	case 3:
		tutorArray.searchByLocation();
		break;
	default:
		cout << "Invalid Entry!";
		searchA();
	}
}

void sortDisplayA() {
	system("cls");
	int choice;
	cout << "Sort and Display\n";
	cout << "1. Sort by ID\n";
	cout << "2. Sort by Rating\n";
	cout << "3. Sort by Salary\n";
	cout << "Enter your choice: ";
	cin >> choice;
	t.rejectChar();
	switch (choice) {
	case 1:
		tutorArray.sortBy(choice);
		break;
	case 2:
		tutorArray.sortBy(choice);
		break;
	case 3:
		tutorArray.sortBy(choice);
		break;
	default:
		cout << "Invalid Entry!";
		sortDisplayA();
	}
	tutorArray.display();
}