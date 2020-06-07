#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "TutorStruct.h"
#include "ConsoleTable.h"
using namespace std;

struct tutorStructArray {
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
};

class TutorArray : public TutorStruct { //extends superclass(TutorStruct)
private:
	vector<tutorStructArray> ts;				//declares a dynamic array of structure
	int idIncrement;					//Used to generate IDs
public:
	TutorArray() : idIncrement(0) {} //Constructor initializing variables

	void addTutor() {
		tutorStructArray s;

		s.tutorID = 100 + idIncrement;

		s.dateJoined = setCurrentDate();
		s.currentRating = 0.0;

		cin.ignore();
		cout << "Enter Name: ";
		getline(cin, s.tutorName);
		cout << "Enter Phone Number: ";
		getline(cin, s.phoneNumber);
		cout << "Enter Address: ";
		getline(cin, s.address);
		cout << "Enter Hour Rate: ";
		cin >> s.hourlyRate;
		while (rejectChar() || s.hourlyRate >= 80 || s.hourlyRate <= 40) {
			cout << "Try again, Enter Hour Rate: ";
			cin >> s.hourlyRate;
		}
		cout << "Enter Center Code: ";
		cin >> s.centerCode;
		cout << "Enter Center Name: ";
		cin.ignore();
		getline(cin, s.centerName);
		cout << "Enter Subject Code:";
		cin >> s.subjectCode;
		cout << "Enter Subject Name: ";
		cin.ignore();
		getline(cin, s.subjectName);
		s.dateTerminated.day = 0; //Terminated day will be set to 0 until reinitialized for a real termination date
		s.dateTerminated.month = 0;
		s.dateTerminated.year = 0;

		ts.push_back(s); //adds the struct info to the vector
		idIncrement++;
	}

	void display() {

		if (ts.data() == NULL) {
			cout << "No data is stored in the database\nRedirecting you to main menu\n";
			return;
		}

		//This output formatting is contributed by github.com/766F6964
		ConsoleTable aTable(BASIC);
		aTable.setPadding(0);
		//Adding comlumns for the table
		aTable.addColumn("ID");
		aTable.addColumn("Name");
		aTable.addColumn("Address");
		aTable.addColumn("Phone");
		aTable.addColumn("Date Joined");
		aTable.addColumn("Rate(RM)");
		aTable.addColumn("Rating");
		aTable.addColumn("Center Code");
		aTable.addColumn("Subject Code");
		aTable.addColumn("Termination Date");

		for (int i = 0; i < ts.size(); i++) { //Print data from every array index
			auto aEntry = new ConsoleTableRow(10);
			aEntry->addEntry(icasts(ts[i].tutorID), 0);
			aEntry->addEntry(ts[i].tutorName, 1);
			aEntry->addEntry(ts[i].address, 2);
			aEntry->addEntry(ts[i].phoneNumber, 3);
			aEntry->addEntry(icasts(ts[i].dateJoined.day) + "-" + icasts(ts[i].dateJoined.month) + "-" + icasts(ts[i].dateJoined.year), 4);
			aEntry->addEntry(dcasts(ts[i].hourlyRate), 5);
			aEntry->addEntry(dcasts(ts[i].currentRating), 6);
			aEntry->addEntry(ts[i].centerCode, 7);
			aEntry->addEntry(ts[i].subjectCode, 8);
			if (ts[i].dateTerminated.day == 0)
				aEntry->addEntry("STILL EMPLOYED", 9);
			else
				aEntry->addEntry(icasts(ts[i].dateTerminated.day) + "-" + icasts(ts[i].dateTerminated.month) + "-" + icasts(ts[i].dateTerminated.year), 9);
			aTable.addRow(aEntry);
		}
		aTable.printTable();
	}

	string icasts(int intR) { //Casts integer into string using stringstream
		stringstream intP;
		intP << intR;
		string str = intP.str();
		return str;
	}

	string dcasts(double doubleR) {//Casts double into string using stringstream
		stringstream doubleP;
		doubleP << doubleR;
		string str = doubleP.str();
		return str;
	}

	//Checks the availability of an ID in the array
	bool checkID(int id) {
		for (int i = 0; i < ts.size(); i++) {
			if (id == ts[i].tutorID) {
				return true;
			}
		}
		return false;
	}

	bool checkRating(double rating) { //Using simple linear search algorithm
		for (int i = 0; i < ts.size(); i++) {
			if (rating == ts[i].currentRating) {
				return true;
			}
		}
		return false;
	}

	bool checkLocation(string location) {
		for (int i = 0; i < ts.size(); i++) {
			if (location == ts[i].address) {
				return true;
			}
		}
		return false;
	}

	void searchByID(int id) { //This is done using Jump Search Algorithm
		int n = sqrt(ts.size()); //The pace is determined as the square root of the array size
		if (checkID(id)) {
			quickSort(ts, 0, ts.size() - 1, 1); //The array is sorted by ID first
			for (int i = 0; i < ts.size(); i += n) {

				if (id == ts[i].tutorID) { //If the pace lands on the wanted value
					printInfo(ts[i]);
					return;
				}
				if (id < ts[i].tutorID) { //If entered ID > tutorID, it performs linear search backwards
					for (int j = i; j > (i - n); j--) {
						if (id == ts[j].tutorID) {
							printInfo(ts[j]);
							return;
						}
					}
				}
			}
			for (int i = (n * n) - 1; i <= ts.size(); i++) { //Checks the rest of the array after index n*n 
				if (id == ts[i].tutorID) {
					printInfo(ts[i]);
					return;
				}
			}
		}
		else
			cout << "Invalid Rating, Try again\n";
	}

	void searchByRating(double rating) { //Since more than one value can be printed, Jump Search couldn't be performed

		if (checkRating(rating)) { //This is done using linear search
			for (int i = 0; i < ts.size(); i++) {
				if (ts[i].currentRating == rating)
					printInfo(ts[i]);
			}
		}
		else
			cout << "Invalid ID, Try again\n";
	}

	void searchByLocation() { //Linear Search for string values
		string location;
		cin.ignore();
		cout << "Enter Location: ";
		getline(cin, location);
		if (checkLocation(location)) {
			for (int i = 0; i < ts.size(); i++) {
				if (ts[i].address == location)
					printInfo(ts[i]);
			}
		}
		else
			cout << "Invalid Location, Try again\n";
	}

	void sortBy(int sortBy) {
		quickSort(ts, 0, ts.size() - 1, sortBy); //A portal function to the Quicksort Algorithm function
	}

	int partition(vector <tutorStructArray>& ts, int low, int high, int sortBy) {
		int pivotIndex = low + (high - low) / 2; //Determines the pivot index using the low and high variables
		int l = low;
		int h = high;
		tutorStructArray temp;

		if (sortBy == 1) { //Sort by ID
			int pivot = ts[pivotIndex].tutorID;
			while (l <= h) {
				while (ts[l].tutorID < pivot) { l++; } //Keeps comparing if a left value is higher than the pivot
				while (ts[h].tutorID > pivot) { h--; } //Keeps comparing if a right value is lower than the pivot
				if (l <= h) { //If a value before the pivot is higher than after the pivot, they swap
					temp = ts[l];
					ts[l] = ts[h];
					ts[h] = temp;
					l++;
					h--;
				}
			}
		}
		if (sortBy == 2) { //Sort by Rating
			double pivot = ts[pivotIndex].currentRating;
			while (l <= h) {
				while (ts[l].currentRating < pivot) { l++; }
				while (ts[h].currentRating > pivot) { h--; }
				if (l <= h) {//If a value before the pivot is higher than after the pivot, they swap
					temp = ts[l];
					ts[l] = ts[h];
					ts[h] = temp;
					l++;
					h--;
				}
			}
		}
		if (sortBy == 3) { //Sort by hourly rate
			double pivot = ts[pivotIndex].hourlyRate;
			while (l <= h) {
				while (ts[l].hourlyRate < pivot) { l++; }
				while (ts[h].hourlyRate > pivot) { h--; }
				if (l <= h) { //If a value before the pivot is higher than after the pivot, they swap
					temp = ts[l];
					ts[l] = ts[h];
					ts[h] = temp;
					l++;
					h--;
				}
			}
		}
		return l;
	}

	void quickSort(vector <tutorStructArray>& ts, int low, int high, int sortBy) {
		if (low < high) {
			int pivotIndex = partition(ts, low, high, sortBy); //It identifies a pivot using the partition function
			quickSort(ts, low, pivotIndex - 1, sortBy); //Recursive for both section before and after the pivot
			quickSort(ts, pivotIndex, high, sortBy);
		}
	}

	void deleteRecord() {
		int id;
		cout << "Enter Tutor ID to delete: ";
		cin >> id;
		rejectChar(); //Rejects entered characters
		if (checkID(id)) {
			int i;
			for (i = 0; i < ts.size(); i++) {
				if (id == ts[i].tutorID)
					break;
			}
			if (ts[i].dateTerminated.day == 0) { //If there is no termination date, it has to be terminated before deleted after 6 months
				char choice;
				cout << "The contract has not been terminated yet, you have to terminate the contract first.\n";
				cout << "Terminate Contract (Y/N): ";
				cin >> choice;
				switch (choice) {
				case 'y':
				case 'Y':
					ts[i].dateTerminated = setCurrentDate(); //Termination date is set to current date
					cout << "\n\nThe contract has been terminated successfully...\n";
					break;
				default:
					return;
				}
				return;
			}

			if (sixMonthCheck(ts[i].dateJoined)) {
				ts.erase(ts.begin() + i); //Array is deleted at i index
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
		int i;
		string strRead;
		double dblRead;
		cout << "Enter Tutor ID to modify: ";
		cin >> id;
		rejectChar();
		if (checkID(id)) {
			for (i = 0; i < ts.size(); i++) {
				if (id == ts[i].tutorID)
					break;
			}
			cout << "\n\nxX ENTER '0' FOR NON-WANTED EDITS Xx\n\n"; //Enter 0 if no edit is wanted
			cin.ignore(); //To catch null entry
			cout << "Phone Number: ";
			getline(cin, strRead); //Gets the value in a temporary variable to check before changing with current values
			if (strRead != "0")
				ts[i].phoneNumber = strRead;
			cout << "Address: ";
			getline(cin, strRead);
			if (strRead != "0")
				ts[i].address = strRead;
			cout << "Hourly Rate: ";
			cin >> dblRead;
			while (rejectChar()) {
				cout << "Try again, Enter Hourly Rate: ";
				cin >> dblRead;
			}
			if (dblRead != 0)
				ts[i].hourlyRate = dblRead;
			cout << "Rating: ";
			cin >> dblRead;
			while (rejectChar() || dblRead > 5 || dblRead < 1) { //Rating can only be accepted if it's from 1 to 5
				cout << "Try again, Enter Rating: ";
				cin >> dblRead;
			}
			if (dblRead != 0)
				ts[i].currentRating = dblRead;
			cout << "The record has been modified successfully...\n";
		}
		else
			cout << "Invalid ID...\n";
	}

	void generateReport() { //Generates a list of currently employed employees
		if (ts.data() == NULL) {
			cout << "No data is stored in the database\nRedirecting you to main menu\n";
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

		for (int i = 0; i < ts.size(); i++) { //If a record has a termination date, it skips
			if (ts[i].dateTerminated.day != 0)
				continue;
			auto entry = new ConsoleTableRow(10);
			entry->addEntry(icasts(ts[i].tutorID), 0);
			entry->addEntry(ts[i].tutorName, 1);
			entry->addEntry(ts[i].address, 2);
			entry->addEntry(ts[i].phoneNumber, 3);
			entry->addEntry(icasts(ts[i].dateJoined.day) + "-" + icasts(ts[i].dateJoined.month) + "-" + icasts(ts[i].dateJoined.year), 4);
			entry->addEntry(dcasts(ts[i].hourlyRate), 5);
			entry->addEntry(dcasts(ts[i].currentRating), 6);
			entry->addEntry(ts[i].centerCode, 7);
			entry->addEntry(ts[i].subjectCode, 8);
			if (ts[i].dateTerminated.day == 0)
				entry->addEntry("EMPLOYED", 9);
			else
				entry->addEntry(icasts(ts[i].dateTerminated.day) + "-" + icasts(ts[i].dateTerminated.month) + "-" + icasts(ts[i].dateTerminated.year), 9);
			ct.addRow(entry);
		}
		ct.printTable();
	}

	void printInfo(tutorStructArray ts) {
		cout << "---------------------------------------------------------------" << endl;
		cout << "ID: " << ts.tutorID << endl;
		cout << "Name: " << ts.tutorName << endl;
		cout << "Address: " << ts.address << endl;
		cout << "Phone Number: " << ts.phoneNumber << endl;
		cout << "Date Joined: " << ts.dateJoined.day << "-" << ts.dateJoined.month << "-" << ts.dateJoined.year << endl;
		cout << "Hourly Rate (RM): " << ts.hourlyRate << endl;
		cout << "Rating (/5): " << ts.currentRating << endl;
		cout << "Center Code: " << ts.centerCode << endl;
		cout << "Subject Code: " << ts.subjectCode << endl;
		if (ts.dateTerminated.day == 0)
			cout << "Termination Date: STILL EMPLOYED\n";
		else
			cout << "Termination Date: " << ts.dateTerminated.day << "-" << ts.dateTerminated.month << "-" << ts.dateTerminated.year << endl;
		cout << "---------------------------------------------------------------" << endl;
	}

	void addDemoData() { //Demo records for presentation purposes
		tutorStructArray a;
		a.tutorID = 333;
		a.tutorName = "Ahmed Qaid";
		a.dateJoined.day = 15;
		a.dateJoined.month = 12;
		a.dateJoined.year = 2005;
		a.hourlyRate = 54.2;
		a.phoneNumber = "0172545897";
		a.address = "Exo Highland";
		a.currentRating = 4;
		a.centerCode = "SOCT";
		a.centerName = "Computing";
		a.subjectCode = "DSTR";
		a.subjectName = "Data Structure";
		a.dateTerminated.day = 0;
		a.dateTerminated.month = 0;
		a.dateTerminated.year = 0;
		ts.push_back(a);
		a.tutorID = 211;
		a.tutorName = "John Smith";
		a.dateJoined.day = 26;
		a.dateJoined.month = 4;
		a.dateJoined.year = 2014;
		a.hourlyRate = 37.5;
		a.phoneNumber = "0167458975";
		a.address = "Mach Lake";
		a.currentRating = 4.7;
		a.centerCode = "SOCT";
		a.centerName = "Computing";
		a.subjectCode = "CS1";
		a.subjectName = "Computing Basics";
		a.dateTerminated.day = 0;
		a.dateTerminated.month = 0;
		a.dateTerminated.year = 0;
		ts.push_back(a);
		a.tutorID = 255;
		a.tutorName = "Lee Wan";
		a.dateJoined.day = 14;
		a.dateJoined.month = 9;
		a.dateJoined.year = 2011;
		a.hourlyRate = 33.0;
		a.phoneNumber = "0154521036";
		a.address = "Bukit Jalil";
		a.currentRating = 4.7;
		a.centerCode = "BS";
		a.centerName = "Business";
		a.subjectCode = "BM";
		a.subjectName = "Business Management";
		a.dateTerminated.day = 29;
		a.dateTerminated.month = 11;
		a.dateTerminated.year = 2018;
		ts.push_back(a);
		a.tutorID = 298;
		a.tutorName = "Anna Sully";
		a.dateJoined.day = 19;
		a.dateJoined.month = 3;
		a.dateJoined.year = 2020;
		a.hourlyRate = 41.5;
		a.phoneNumber = "0154789656";
		a.address = "Bukit Jalil";
		a.currentRating = 4.1;
		a.centerCode = "BS";
		a.centerName = "Business";
		a.subjectCode = "BA";
		a.subjectName = "Business Administration";
		a.dateTerminated.day = 0;
		a.dateTerminated.month = 0;
		a.dateTerminated.year = 0;
		ts.push_back(a);
	}

	void view() {
		if (ts.data() == NULL) {
			cout << "No data is stored in the database\nRedirecting you to main menu\n";
			return;
		}
		
		int i = 0;
		while (true) {
			cout << "---------------------------------------------------------------" << endl;
			cout << "ID: " << ts[i].tutorID << endl;
			cout << "Name: " << ts[i].tutorName << endl;
			cout << "Address: " << ts[i].address << endl;
			cout << "Phone Number: " << ts[i].phoneNumber << endl;
			cout << "Date Joined: " << ts[i].dateJoined.day << "-" << ts[i].dateJoined.month << "-" << ts[i].dateJoined.year << endl;
			cout << "Hourly Rate (RM): " << ts[i].hourlyRate << endl;
			cout << "Rating (/5): " << ts[i].currentRating << endl;
			cout << "Center Code: " << ts[i].centerCode << endl;
			cout << "Subject Code: " << ts[i].subjectCode << endl;
			if (ts[i].dateTerminated.day == 0)
				cout << "Termination Date: STILL EMPLOYED\n";
			else
				cout << "Termination Date: " << ts[i].dateTerminated.day << "-" << ts[i].dateTerminated.month << "-" << ts[i].dateTerminated.year << endl;
			cout << "---------------------------------------------------------------" << endl;

			char n;
			cout << "Enter 'N' for next, 'P' for previous: ";
			cin >> n;
			if (n == 'n') {
				i++;
				system("cls");
				if (i == ts.size()) {
					cout << "You have reached the end of the list\n";
					break;
				}
			}
			else if (n == 'p') {
				i--;
				system("cls");
				if (i == -1) {
					cout << "You have reached the end of the list\n";
					break;
				}
			}
			else
				break;
		}
	}
};