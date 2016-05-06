#ifndef INPUT_H
#define INPUT_H

#include <climits>

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	char &value: The variable to store the value 
//	const char *msg: The message to display to the user
void GetInput(char &value, const char *msg);

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	int &value: The variable to store the value 
//	const char *msg: The message to display to the user
//	int min: the minimum value the input can take
//	int max: the maximum value the input can take
void GetInput(int &value, const char *msg, int min = INT_MIN, int max = INT_MAX);

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	double &value: The variable to store the value 
//	const char *msg: The message to display to the user
//	double min: the minimum value the input can take
//	double max: the maximum value the input can take
void GetInput(double &value, const char *msg, double min = -1e99, double max = 1e99);

//Function: GetInput
//Purpose: Gets input from stdin and error checks it
//Parameters:
//	float &value: The variable to store the value 
//	const char *msg: The message to display to the user
//	float min: The minimum value the input can take
//	float max: The maximum value the input can take
void GetInput(float &value, const char *msg, float min = -1e99, float max = 1e99);

//Function: GetInput
//Purpose: Get a string from stdin and error check
//Parameters:
//	std::string &value: the value to store the string in
//	const char *msg: The message to display to the user
void GetInput(std::string &value, const char *msg);

#endif
