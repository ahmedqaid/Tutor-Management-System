#pragma once
#include <iostream>
#include <ctime>
#pragma warning (disable: 4996)
using namespace std;

struct date {
	int day;
	int month;
	int year;
};

class TutorStruct {
public:

	date setCurrentDate() { //Gets current date from the system
		date date;
		time_t ttime = time(0);
		tm* local_time = localtime(&ttime);

		date.year = 1900 + local_time->tm_year;
		date.month = 1 + local_time->tm_mon;
		date.day = local_time->tm_mday;
		return date;
	}

	//Counts days, months and years to determine if 6 months have passed for the record
	bool sixMonthCheck(date dateTerminated) {
		date currentDate = setCurrentDate();
		date howago;
		howago.year = currentDate.year - (dateTerminated.year + 1);
		howago.month = 0;
		if (currentDate.month > dateTerminated.month)
			howago.month = currentDate.month - dateTerminated.month;
		else if (dateTerminated.month > currentDate.month)
			howago.month = currentDate.month - dateTerminated.month + 12;
		
		if (howago.year > 0)
			return true;
		else if (howago.month > 6)
			return true;
		else
			return false;
	}

	bool rejectChar() { //catches failed input and clears cin memory
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return true; //return true if it rejected a value
		}
		return false;
	}
};