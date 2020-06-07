#pragma once
#include <iostream>
#include <string>
#include "TutorStruct.h"
#include "ConsoleTable.h"
using namespace std;

struct tutorStructList {
	int tutorID;
	string tutorName;
	date dateJoined;
	date dateTerminated;
	double hourlyRate;//    ----
	string phoneNumber;//		 \______ Only these 4 variables 
	string address;//			 /	     are modifiable
	double currentRating;// ----
	string centerCode;
	string centerName;
	string subjectCode;
	string subjectName;

	tutorStructList* next;
	tutorStructList* prev;
};

class TutorLinkedList : public TutorStruct { //extends superclass(TutorStruct)
private:
	int idIncrement = 0; //This variable keeps track of the ID count for dynamic ID feeding
	tutorStructList* list, * newnode, * temp, * head, * tail; //declaring pointer-type variables
public:
	TutorLinkedList() : list(NULL), newnode(NULL), temp(NULL), head(NULL), tail(NULL) { }
	//initializing pointer-type variables

	void addTutor() {
		tutorStructList f;
		f.tutorID = 100 + idIncrement; //The increment is added to 100 to get an ID number

		f.dateJoined = setCurrentDate(); //Sets joine date to current date
		f.currentRating = 0.0; //Starts with 0 for the modification feature

		//To catch the new line instead of being read by the next getline() function
		cin.ignore();
		cout << "Enter Name: ";
		getline(cin, f.tutorName);
		cout << "Enter Phone Number: ";
		getline(cin, f.phoneNumber);
		cout << "Enter Address: ";
		getline(cin, f.address);
		cout << "Enter Hour Rate: ";
		cin >> f.hourlyRate;
		while (rejectChar() || f.hourlyRate >= 80 || f.hourlyRate <= 40) { //Will keep repeating until it finds the proper datatype
			cout << "Try again, Enter Hour Rate: ";
			cin >> f.hourlyRate;
		}
		cout << "Enter Center Code: ";
		cin >> f.centerCode;
		cout << "Enter Center Name: ";
		cin.ignore();
		getline(cin, f.centerName);
		cout << "Enter Subject Code: ";
		cin >> f.subjectCode;
		cout << "Enter Subject Name: ";
		cin.ignore();
		getline(cin, f.subjectName);
		f.dateTerminated.day = 0;
		f.dateTerminated.month = 0;
		f.dateTerminated.year = 0;

		insert(f);
		idIncrement++;
	}

	//called inside addTutor() to store tutor information
	void insert(struct tutorStructList tr) {
		newnode = new tutorStructList;
		newnode->tutorID = tr.tutorID;
		newnode->tutorName = tr.tutorName;
		newnode->dateJoined = tr.dateJoined;
		newnode->hourlyRate = tr.hourlyRate;
		newnode->phoneNumber = tr.phoneNumber;
		newnode->address = tr.address;
		newnode->currentRating = tr.currentRating;
		newnode->centerCode = tr.centerCode;
		newnode->centerName = tr.centerName;
		newnode->subjectCode = tr.subjectCode;
		newnode->subjectName = tr.subjectName;
		newnode->dateTerminated = tr.dateTerminated;
		newnode->next = NULL;
		newnode->prev = NULL; //DLL

		if (list == NULL) { //In case the list is empty, it will just add the record
			list = tail = newnode;
		}
		else { //Otherwise, the record will be added at the end
			newnode->prev = tail;
			tail->next = newnode;
			tail = newnode;
		}
	}

	void searchByID(int id) {
		if (checkID(id)) { //Checks if the entered ID is available
			temp = list;
			//Linear search performed by comparing IDs to the entered ID
			while (temp->tutorID != id) {
				head = temp;
				temp = temp->next;
			}
			printInfo(temp);
		}
		else
			cout << "Invalid ID, Try again\n";
	}

	bool checkID(int id) {
		temp = list;

		while (temp->tutorID != id) { //continue as long as there is no match
			if (temp == tail)
				return false; //Returning false when the temp has reached the end of the list
			head = temp;
			temp = temp->next; //navigate to the next node
		}
		return true;
	}

	void searchByRating(double rating) {
		if (checkRating(rating)) {
			temp = list;

			while (true) {
				
				if (temp->currentRating == rating) {
					printInfo(temp);
				}
				if (temp == tail)
					break;
				temp = temp->next;
			}
		}
		else
			cout << "Invalid Rating, Try again\n";
	}

	bool checkRating(double rating) {
		temp = list;

		while (temp->currentRating != rating) {
			if (temp == tail)
				return false;
			head = temp;
			temp = temp->next;
		}
		return true;
	}

	void searchByLocation() {
		string location;
		cout << "Enter Location: ";
		cin.ignore();
		getline(cin, location);
		if (checkLocation(location)) {
			temp = list;

			while (true) {

				if (temp->address == location) {
					printInfo(temp);
				}
				if (temp == tail)
					break;
				temp = temp->next;
			}
		}
		else
			cout << "Invalid Location, Try again\n";
	}

	bool checkLocation(string address) {
		temp = list;

		while (temp->address != address) {
			if (temp == tail)
				return false;
			head = temp;
			temp = temp->next;
		}
		return true;
	}

	void display() {
		if (list == NULL) { //Checks if there is no record in the database to return back
			cout << "No data is stored in the database\nRedirecting to main menu\n";
			return;
		}

		//This output formatting is contributed by github.com/766F6964

		ConsoleTable lTable(BASIC); //Declares a table
		lTable.setPadding(0);

		lTable.addColumn("ID");
		lTable.addColumn("Name");
		lTable.addColumn("Address");
		lTable.addColumn("Phone");
		lTable.addColumn("Date Joined");
		lTable.addColumn("Rate(RM)");
		lTable.addColumn("Rating");
		lTable.addColumn("Center Code");
		lTable.addColumn("Subject Code");
		lTable.addColumn("Termination Date");


		temp = list;
		while (temp != NULL) { //Reading every node and adding its data to the table
			auto lEntry = new ConsoleTableRow(10); //declaring a row with 10 columns
			lEntry->addEntry(icasts(temp->tutorID), 0); //ints and doubles should be casted to strings before adding to the table
			lEntry->addEntry(temp->tutorName, 1);
			lEntry->addEntry(temp->address, 2);
			lEntry->addEntry(temp->phoneNumber, 3);
			lEntry->addEntry(icasts(temp->dateJoined.day) + "-" + icasts(temp->dateJoined.month) + "-" + icasts(temp->dateJoined.year), 4);
			lEntry->addEntry(dcasts(temp->hourlyRate), 5);
			lEntry->addEntry(dcasts(temp->currentRating), 6);
			lEntry->addEntry(temp->centerCode, 7);
			lEntry->addEntry(temp->subjectCode, 8);
			if (temp->dateTerminated.day == 0) //providing that day still has 0 value, means there is no actual termination date
				lEntry->addEntry("STILL EMPLOYED", 9);
			else
				lEntry->addEntry(icasts(temp->dateTerminated.day) + "-" + icasts(temp->dateTerminated.month) + "-" + icasts(temp->dateTerminated.year), 9);
			lTable.addRow(lEntry); //adding the row to the table
			temp = temp->next;
		}
		lTable.printTable(); //displays the table
	}

	string icasts(int intR) { //This function casts int values to strings
		stringstream intP; //Declaring a stringstream variable
		intP << intR;	//move data from int variable to string variable
		string str = intP.str(); //making the variable a string
		return str; //Return the casted int value (string)
	}

	string dcasts(double doubleR) { //This function casts double values to strings
		stringstream doubleP;
		doubleP << doubleR;
		string str = doubleP.str();
		return str;
	}

	void sortBy(int sortBy) { //A portal function that takes a value and pass it into the sorting function
		mergeSort(&list, sortBy); //The list address and the sort choice are passed
		display();
	}

	void mergeSort(tutorStructList** beginning, int sortBy) {
		tutorStructList* head = *beginning;
		tutorStructList* section1, * section2;
		if (head->next == NULL || head == NULL) //Considering there is no more records after the head
			return;
		split(head, &section1, &section2); //Splits the list section into 2 sections
		mergeSort(&section1, sortBy); // Recurse by splitting the list until it's single
		mergeSort(&section2, sortBy);
		*beginning = mergeLinkedList(section1, section2, sortBy); //It will merge the list and swap for correct indices
	}

	void split(tutorStructList* beginning, tutorStructList** section1, tutorStructList** section2) {
		tutorStructList* first = beginning;
		tutorStructList* second = beginning->next;

		while (second != NULL) { //Implementing "The Tortoise and the Hare" (Floyd’s Algorithm)
			second = second->next;
			if (second != NULL) {
				first = first->next;
				second = second->next;
			}
		}
		*section1 = beginning;
		*section2 = first->next;
		//To split
		first->next = NULL;
	}

	tutorStructList* mergeLinkedList(tutorStructList* section1, tutorStructList* section2, int sortBy) {
		tutorStructList* newnode = NULL;
		if (section1 == NULL)
			return section2;
		if (section2 == NULL)
			return section1;

		//Recursive Merging, Comparing and Swapping
		//Sort by choice, 1: sort by ID, 2: sort by rating, 3: sort by salary
		if (sortBy == 1) {
			if (section1->tutorID <= section2->tutorID) {
				newnode = section1;
				newnode->next = mergeLinkedList(section1->next, section2, sortBy);
			}
			else {
				newnode = section2;
				newnode->next = mergeLinkedList(section1, section2->next, sortBy);
			}
		}
		else if (sortBy == 2) {
			if (section1->currentRating <= section2->currentRating) {
				newnode = section1;
				newnode->next = mergeLinkedList(section1->next, section2, sortBy);
			}
			else {
				newnode = section2;
				newnode->next = mergeLinkedList(section1, section2->next, sortBy);
			}
		}
		else if (sortBy == 3) {
			if (section1->hourlyRate <= section2->hourlyRate) {
				newnode = section1;
				newnode->next = mergeLinkedList(section1->next, section2, sortBy);
			}
			else {
				newnode = section2;
				newnode->next = mergeLinkedList(section1, section2->next, sortBy);
			}
		}

		return newnode;
	}

	void deleteRecord() {
		int id;
		cout << "Enter Tutor ID to delete: ";
		cin >> id;
		rejectChar();
		if (checkID(id)) { //Checking ID availability
			temp = list;
			while (temp->tutorID != id) {  //The moment it finds the list, the loop stops
				head = temp;
				temp = temp->next;
			}
			if (temp->dateTerminated.day == 0) { //Id there is no termination date, prompt a termination decision
				char choice;
				cout << "The contract has not been terminated yet, you have to terminate the contract first.\n";
				cout << "Terminate Contract (Y/N): ";
				cin >> choice;
				switch (choice) {
				case 'y':
				case 'Y':
					temp->dateTerminated = setCurrentDate(); //The current date will be saved as termination date
					cout << "\n\nThe contract has been terminated successfully...\n";
					break;
				default:
					return;
				}
				return;
			}

			else if (sixMonthCheck(temp->dateTerminated)) {
				if (temp == list) { //Deleting at the beginning
					temp = list;
					list->next->prev = NULL;
					list = list->next;
					delete temp;
				}
				else if (temp == tail) { //Deleting at the end
					temp = tail;
					tail->prev->next = NULL;
					tail = tail->prev;
					delete temp;
				}
				else { //Deleting in the middle+
					head->next = head->next->next;
					temp->next->prev = head;
					delete temp;
				}
				cout << "Record Deleted Successfully...\n";
			}
			else
				cout << "The six-month period has not passed for this tutor yet...\n";

		}
		else
			cout << "Invalid ID, Try again\n";
	}

	void modifyRecord() {
		int id;
		string strRead;
		double dblRead;
		cout << "Enter Tutor ID to modify: ";
		cin >> id;
		rejectChar();
		if (checkID(id)) {
			temp = list;
			while (temp->tutorID != id) {
				head = temp;
				temp = temp->next;
			}
			cout << "\n\nxX ENTER '0' FOR NON-WANTED EDITS Xx\n\n"; //The modification window will allow the user to modify
																	//The modifying can occur noting that entering '0' skips
			cout << "Phone Number: ";
			cin.ignore();
			getline(cin, strRead); //A temporary variable reads the value entered to ensure modification is working at best
			if (strRead != "0")					//No messed data
				temp->phoneNumber = strRead;
			cout << "Address: ";
			getline(cin, strRead);
			if (strRead != "0")
				temp->address = strRead;
			cout << "Hourly Rate: ";
			cin >> dblRead;
			while (rejectChar()) { //Keep asking for valid entries
				cout << "Try again, Enter Hourly Rate: ";
				cin >> dblRead;
			}
			if (dblRead != 0)
				temp->hourlyRate = dblRead;
			cout << "Rating: ";
			cin >> dblRead;
			while (rejectChar() || dblRead > 5 || dblRead < 1) { //If char or a number not between 1 and 5, it passes
				cout << "Try again, Enter Rating: ";
				cin >> dblRead;
			}
			if (dblRead != 0)
				temp->currentRating = dblRead;
			cout << "The record has been modified successfully...\n";
		}
		else
			cout << "Invalid ID...\n";
	}

	void generateReport() { //This report is generated to display who are still have an available status
		if (list == NULL) {
			cout << "No data is stored in the database\nRedirecting to main menu\n";
			return;
		}
		ConsoleTable ct(BASIC);
		ct.setPadding(0);

		ct.addColumn("ID");
		ct.addColumn("Name");
		ct.addColumn("Address");
		ct.addColumn("Phone");
		ct.addColumn("Date Joined");
		ct.addColumn("Rate(RM)");
		ct.addColumn("Rating");
		ct.addColumn("Center Code");
		ct.addColumn("Subject Code");
		ct.addColumn("Status");


		temp = list;
		while (temp != NULL) {
			if (temp->dateTerminated.day != 0) { //Skips records with termination dates
				temp = temp->next;
				continue;
			}
			auto entry = new ConsoleTableRow(10);
			entry->addEntry(icasts(temp->tutorID), 0);
			entry->addEntry(temp->tutorName, 1);
			entry->addEntry(temp->address, 2);
			entry->addEntry(temp->phoneNumber, 3);
			entry->addEntry(icasts(temp->dateJoined.day) + "-" + icasts(temp->dateJoined.month) + "-" + icasts(temp->dateJoined.year), 4);
			entry->addEntry(dcasts(temp->hourlyRate), 5);
			entry->addEntry(dcasts(temp->currentRating), 6);
			entry->addEntry(temp->centerCode, 7);
			entry->addEntry(temp->subjectCode, 8);
			if (temp->dateTerminated.day == 0)
				entry->addEntry("EMPLOYED", 9);
			else
				entry->addEntry(icasts(temp->dateTerminated.day) + "-" + icasts(temp->dateTerminated.month) + "-" + icasts(temp->dateTerminated.year), 9);
			ct.addRow(entry);
			temp = temp->next;
		}
		ct.printTable();
	}

	void addDemoData() { //Adding data for presentation
		tutorStructList t;
		t.tutorID = 333;
		t.tutorName = "Ahmed Qaid";
		t.dateJoined.day = 15;
		t.dateJoined.month = 12;
		t.dateJoined.year = 2005;
		t.hourlyRate = 54.2;
		t.phoneNumber = "0172545897";
		t.address = "Exo Highland";
		t.currentRating = 4;
		t.centerCode = "SOCT";
		t.centerName = "Computing";
		t.subjectCode = "DSTR";
		t.subjectName = "Data Structure";
		t.dateTerminated.day = 0;
		t.dateTerminated.month = 0;
		t.dateTerminated.year = 0;
		insert(t);
		t.tutorID = 211;
		t.tutorName = "John Smith";
		t.dateJoined.day = 26;
		t.dateJoined.month = 4;
		t.dateJoined.year = 2014;
		t.hourlyRate = 37.5;
		t.phoneNumber = "0167458975";
		t.address = "Mach Lake";
		t.currentRating = 4.7;
		t.centerCode = "SOCT";
		t.centerName = "Computing";
		t.subjectCode = "CS1";
		t.subjectName = "Computing Basics";
		t.dateTerminated.day = 0;
		t.dateTerminated.month = 0;
		t.dateTerminated.year = 0;
		insert(t);
		t.tutorID = 255;
		t.tutorName = "Lee Wan";
		t.dateJoined.day = 14;
		t.dateJoined.month = 9;
		t.dateJoined.year = 2011;
		t.hourlyRate = 33.0;
		t.phoneNumber = "0154521036";
		t.address = "Bukit Jalil";
		t.currentRating = 4.7;
		t.centerCode = "BS";
		t.centerName = "Business";
		t.subjectCode = "BM";
		t.subjectName = "Business Management";
		t.dateTerminated.day = 29;
		t.dateTerminated.month = 11;
		t.dateTerminated.year = 2018;
		insert(t);
		t.tutorID = 298;
		t.tutorName = "Anna Sully";
		t.dateJoined.day = 19;
		t.dateJoined.month = 3;
		t.dateJoined.year = 2020;
		t.hourlyRate = 41.5;
		t.phoneNumber = "0154789656";
		t.address = "Bukit Jalil";
		t.currentRating = 4.1;
		t.centerCode = "BS";
		t.centerName = "Business";
		t.subjectCode = "BA";
		t.subjectName = "Business Administration";
		t.dateTerminated.day = 0;
		t.dateTerminated.month = 0;
		t.dateTerminated.year = 0;
		insert(t);
	}

	void printInfo(tutorStructList* temp) { //Multi purpose printing especially for search results
		cout << "---------------------------------------------------------------" << endl;
		cout << "ID: " << temp->tutorID << endl;
		cout << "Name: " << temp->tutorName << endl;
		cout << "Address: " << temp->address << endl;
		cout << "Phone Number: " << temp->phoneNumber << endl;
		cout << "Date Joined: " << temp->dateJoined.day << "-" << temp->dateJoined.month << "-" << temp->dateJoined.year << endl;
		cout << "Hourly Rate (RM): " << temp->hourlyRate << endl;
		cout << "Rating (/5): " << temp->currentRating << endl;
		cout << "Center Code: " << temp->centerCode << endl;
		cout << "Subject Code: " << temp->subjectCode << endl;
		if (temp->dateTerminated.day == 0)
			cout << "Termination Date: STILL EMPLOYED\n";
		else
			cout << "Termination Date: " << temp->dateTerminated.day << "-" << temp->dateTerminated.month << "-" << temp->dateTerminated.year << endl;
		cout << "---------------------------------------------------------------" << endl;
	}

	void view() {
		temp = list;
		while (temp != NULL) {
			cout << "---------------------------------------------------------------" << endl;
			cout << "ID: " << temp->tutorID << endl;
			cout << "Name: " << temp->tutorName << endl;
			cout << "Address: " << temp->address << endl;
			cout << "Phone Number: " << temp->phoneNumber << endl;
			cout << "Date Joined: " << temp->dateJoined.day << "-" << temp->dateJoined.month << "-" << temp->dateJoined.year << endl;
			cout << "Hourly Rate (RM): " << temp->hourlyRate << endl;
			cout << "Rating (/5): " << temp->currentRating << endl;
			cout << "Center Code: " << temp->centerCode << endl;
			cout << "Subject Code: " << temp->subjectCode << endl;
			if (temp->dateTerminated.day == 0)
				cout << "Termination Date: STILL EMPLOYED\n";
			else
				cout << "Termination Date: " << temp->dateTerminated.day << "-" << temp->dateTerminated.month << "-" << temp->dateTerminated.year << endl;
			cout << "---------------------------------------------------------------" << endl;
			
			char n;
			cout << "Enter 'N' for next, 'P' for previous: ";
			cin >> n;
			if (n == 'n') {
				temp = temp->next;
				system("cls");
				if (temp == NULL)
					cout << "You have reached the end of the list\n";
			}
			else if (n == 'p') {
				temp = temp->prev;
				system("cls");
				if (temp == NULL)
					cout << "You have reached the end of the list\n";
			}
			else
				break;
		}

	}
};