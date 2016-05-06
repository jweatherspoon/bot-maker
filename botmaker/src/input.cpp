//======================================================================================================
//Program Name: input.cpp
//Purpose: Handles error checking when getting input from stdin
//Author: Jonathan Weatherspoon
//======================================================================================================

#include <iostream>
#include <string>
#include "headers/input.h"

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	char &value: The variable to store the value 
//	const char *msg: The message to display to the user
void GetInput(char &value, const char *msg) {
	while(true) {
		std::cout << msg;
		if((std::cin >> value)) break;
		
		std::cin.clear(); //Clear the bad flag
		std::cin.ignore(1000, '\n'); //Clear the rest of the line
	}
}

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	int &value: The variable to store the value 
//	const char *msg: The message to display to the user
//	int min: the minimum value the input can take
//	int max: the maximum value the input can take
void GetInput(int &value, const char *msg, int min, int max) {
	while(true) {
		std::cout << msg;
		if((std::cin >> value)) {
			//input is good, check bounds now
			if(value >= min && value <= max) break; 
		}
		
		std::cin.clear(); //Clear the bad flag
		std::cin.ignore(1000, '\n'); //Clear the rest of the line
	}
}

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	double &value: The variable to store the value 
//	const char *msg: The message to display to the user
//	double min: the minimum value the input can take
//	double max: the maximum value the input can take
void GetInput(double &value, const char *msg, double min, double max) {
	while(true) {
		std::cout << msg;
		if((std::cin >> value)) {
			//input is good, check bounds now
			if(value >= min && value <= max) break; 
		}
		
		std::cin.clear(); //Clear the bad flag
		std::cin.ignore(1000, '\n'); //Clear the rest of the line
	}
}

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	float &value: The variable to store the value 
//	const char *msg: The message to display to the user
//	float min: The minimum value the input can take
//	float max: the maximum value the input can take
void GetInput(float &value, const char *msg, float min, float max) {
	while(true) {
		std::cout << msg;
		if((std::cin >> value)) {
			//input is good, check bounds now
			if(value >= min && value <= max) break; 
		}
		
		std::cin.clear(); //Clear the bad flag
		std::cin.ignore(1000, '\n'); //Clear the rest of the line
	}
}


//Function: GetInput
//Purpose: Get a string from stdin and error check
//Parameters:
//	std::string &value: the value to store the string in
//	const char *msg: The message to display to the user
void GetInput(std::string &value, const char *msg) {
	while(true) {
		std::cout << msg;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		if((std::cin >> value)) break;
	}
}

