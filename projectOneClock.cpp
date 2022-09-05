/*********************
Ronald W. Sudol III

SNHU Computer Science

CS-210 Project One

07/17/2022

**********************/


#include <iostream>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <string>
#include <thread>

#pragma warning(disable : 4996)				//this disables an error that was telling me the values for
											// time were deprecated? program runs fine now.

using namespace std;

int userPlusHour = 0;					//token variables and bools that were easier to pass this way
int userPlusMinute = 0;					// not sure if maybe i should have used classes somehow?
int userPlusSecond = 0;
bool CONTINUE_RUN = true;

//functions:
string twoDigitString(int n) {
	string strOut = "0";
		if (n < 10) {				// acounts for just single digit numbers requiring a preceding '0'
			strOut = strOut += to_string(n);
		}
		else {
			strOut = to_string(n);
		}
	return strOut;
}

string nCharString(int x, char y) { // create a string of char y that is x in length
	int i;
	string strOut;
	for (i = 0; i < x; i++) {
		strOut += y;
	}
	return strOut;
}

string formatTime24(int x, int y, int z) {			//sets time for 24hr format and account for time added by user
	string strOut;
	strOut = twoDigitString((x + userPlusHour) % 24) + ":" + twoDigitString((y + userPlusMinute) % 60) + ":" 
		+ twoDigitString((z + userPlusSecond) % 60);
	return strOut;
}
	
string formatTime12(int x, int y, int z) {// format time to 12hr scale and add value for AM or PM
	string strOut;
	string amPm;
	
	x = (x + userPlusHour) % 24;		//accounts for time increments added by users selection
	y = (y + userPlusMinute) % 60;
	z = (z + userPlusSecond) % 60;
	
	if (x >= 12) { // sets the value of AM or PM
		amPm = "PM";
	}
	else if (x < 12) {
		amPm = "AM";
	}
	
	
	if (x > 12) { // accounts for 12 hour scale
		x -= 12;
	}
	else if (x == 0) { //acounts for midnight as '0'
		x = 12;
	}
	strOut = twoDigitString(x) + ":" + twoDigitString(y) + ":" + twoDigitString(z) + " " + amPm;

	return strOut;
}

void displayClocks(int hour, int minute, int second) {		// sets the format for the clock display and prints display
	cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
	cout << "*" << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << "*   *" << nCharString(6, ' ')
		<< "24-HOUR CLOCK" << nCharString(6, ' ') << "*" << endl;
	cout << "*" << nCharString(6, ' ') << formatTime12(hour, minute, second) << nCharString(8, ' ') << "*   *"
		<< nCharString(8, ' ') << formatTime24(hour, minute, second) << nCharString(9, ' ') << "*" << endl;
	cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
}


void printMenu() {			// formats and prints menu display
	cout << nCharString(27, '*') << endl;
	cout << "* 1-Add One Hour  " << nCharString(8, ' ') << "*" << endl;
	cout << "* 2-Add One Minute" << nCharString(8, ' ') << "*" << endl;
	cout << "* 3-Add One Second" << nCharString(8, ' ') << "*" << endl;
	cout << "* 4-Exit Program  " << nCharString(8, ' ') << "*" << endl;
	cout << nCharString(27, '*') << endl;
	
}


void getMenuChoice(int x) {		//read input from menu and execute
	printMenu();
	x = getch();				//gets next keystroke from user
	if(x == 49) {				//converts ascii values from getch() to integers
		x = 1;
	}
	if(x == 50) {
		x = 2;
	}
	if(x == 51) {
		x = 3;
	}
	if (x == 52) {
		x = 4;
	}

	if (x == 1) {					//reads selected option and increments designated token
		userPlusHour += 1;
	}
	else if (x == 2) {
		userPlusMinute += 1;
	}
	else if (x == 3) {
		userPlusSecond += 1;
	}
	else if (x == 4) {				//this option changes bool value that continues while loop in main
		CONTINUE_RUN = false;		//exits program
	}
	else {							//this ensures that user input is valid choice and resets time and menu with alert
		system("cls");
		cout << "INVALID ENTRY" << endl;
		time_t now = time(0);
		tm* local_time = localtime(&now);
		int hour = local_time->tm_hour;
		int minute = local_time->tm_min;
		int second = local_time->tm_sec;
		
		displayClocks(hour, minute, second);
		
		getMenuChoice(0);
	}
}

int main() {
	
	while (CONTINUE_RUN == true) {			//while loop continues while boolean value is true
		time_t now = time(0);				//imports current time to be passed to functions
		tm* local_time = localtime(&now);
		int hour = local_time->tm_hour;		//sets time values to passable int variables
		int minute = local_time->tm_min;
		int second = local_time->tm_sec;

		
		
		displayClocks(hour, minute, second);	//calls clock... clock will update real time if menu is commented out
													// i struggled to incorporate menu so that it wouldn't
													// interfere with the ticking of the clock
		getMenuChoice(0);						//this prints the menu and uses getch() to recieve next keystroke
													
		system("cls");							//clears screen
		
		
	}


	return 0;
}