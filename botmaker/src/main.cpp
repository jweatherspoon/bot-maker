//======================================================================================================
//Program Name: main.cpp
//Purpose: 
//Author: Jonathan Weatherspoon
//======================================================================================================

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "headers/bot.h"
#include "headers/window.h"
#include "headers/input.h"

#define MENU_EXIT 7

Bot *bot = NULL;
std::string botName = "";

//FUNCTION PROTOTYPES
bool PrintMenu();
bool GetUserSelection();

bool OpenAndReadFile(Bot *);

bool CreateBot();

bool CheckBotMenu();
bool SetBotMenu();

void GetCoordinates();

//MAIN FUNCTION: Entry point of the application.
int main(int argc, char **argv) {
	
	//Clear screen
	std::cout << "\x1B[2J\x1B[H";
	while(PrintMenu()) ;
	
	return 0;
}

//Function: PrintMenu
//Purpose: Print a ui to the user
//Return false to terminate the program
bool PrintMenu() {
	
	std::cout << "Make / Use a Bot!" << std::endl
		<< "==============================================" << std::endl
		<< "1) Create a bot" << std::endl
		<< "2) Use existing bot" << std::endl
		<< "3) Check a bot's values" << std::endl
		<< "4) Set a bot's values" << std::endl
		<< "5) Start the current bot" << std::endl
		<< "6) Get current mouse coordinates" << std::endl;
	std::cout << MENU_EXIT << ") Exit program" << std::endl << std::endl;
	
	if(bot) {
		std::cout << "Current Bot: " << botName << std::endl << std::endl;	
	}
	
	return GetUserSelection();
}

//Function: GetUserSelection
//Purpose: Allow the user to choose something from the menu
//Return false when the user wants to exit program
bool GetUserSelection() {
	int selection, i;
	GetInput(selection, "Enter a selection: ", 1, MENU_EXIT);
	
	std::cout << "\x1b[2J\x1B[H"; //Clear the screen
	
	if(bot || selection == 1 || selection == 2 ||
	   selection == 6 || selection == MENU_EXIT) {
		switch(selection) {
			case 1:
				CreateBot();
				break;
			case 2:
				if(bot) delete bot;
				else bot = new Bot();
				OpenAndReadFile(bot);
				break;
			case 3:
				while(CheckBotMenu()) ;
				break;
			case 4:
				while(SetBotMenu()) ;
				break;
			case 5:
				GetInput(selection, "How many seconds before start? ", 0);
				std::cout << "Starting bot in " << selection << " seconds...";
				usleep(selection * 1000 * 1000);
				std::cout << std::endl << "Starting bot..." << std::endl;
				bot->StartBot();
				break;
			case 6: {
				POINT tmp;
				GetCursorPos(tmp);
				std::cout << "Current coordinates: " << tmp << std::endl;
				break;
			}
			case MENU_EXIT: 
				if(bot) {
					std::ofstream fout(("bots/" + botName).c_str());
					fout << *bot;
					fout.close();
					delete bot;
				}
				return false;
				break;
			default:
				std::cout << "Unrecognized input: " << selection << std::endl;
		}
	} else {
		std::cout << std::endl << "No bot currently active!" << std::endl;	
	}
	
	return true;
}

//Function: OpenAndReadFile
//Purpose: Open and read a data file
//Parameters:
//	Bot *b: The bot to populate with data
//Returns false if the operation failed
bool OpenAndReadFile(Bot *b) {
	std::cout << "Enter a filename: bots/";
	
	std::ifstream fin;
	do {
		std::cin >> botName;
		fin.open(("bots/" + botName).c_str());
		if(!fin) std::cout << "Could not open file! Try again: ";
	} while(!fin);
	
	//File now open. Read in data
	fin >> *b;
	
	fin.close();
	
	return true;
}

//Function: CreateBot
//Purpose: Create a new bot 
//Returns false if anything failed
bool CreateBot() {
	int itmp, i, numMsgs = 0;
	POINT ptmp;
	std::string stmp;
	char ch;
	
	std::ofstream fout;
	
	//Clear screen
	std::cout << "\x1B[2J\x1B[h";
	
	GetInput(stmp, "Enter the name of this bot (no spaces!): bots/");
	fout.open(("bots/" + stmp).c_str());
	if(!fout) {
		std::cerr << "Failed to open file: bots/" << stmp << " for reading!" << std::endl;
		return false;
	}
	
	Bot tmp;
	
	GetInput(itmp, "Enter the number of clicks this bot should perform: ", 0);
	std::cin.ignore(1000, '\n'); //Clear so the terminal will wait
	
	//Should allocate memory for all needed members
	tmp.SetNumClicks(itmp);
	
	//Saves a bunch of calls to GetNumClicks at the very least
	if(itmp > 0) {
		//Get the points to click yo
		for(i = 0; i < tmp.GetNumClicks(); i++) {
			std::cout << "Move the cursor to the position you want to click and press enter: ";
			std::cin.ignore();
			GetCursorPos(ptmp);
			tmp.SetPoint(ptmp, i);
			std::cout << "Click " << i << " has been set to coordinates: " << ptmp << std::endl;
		}

		//Get the times for each click
		for(i = 0; i < tmp.GetNumClicks(); i++) {
			std::cout << "Enter the number of seconds to wait after click " << i << std::endl 
				<< "at coordinates ( " << tmp.GetPoint(i) << " ): ";
			GetInput(itmp, "");
			tmp.SetClickTime(itmp, i);
		}

		//Get the type after click members
		for(i = 0; i < tmp.GetNumClicks(); i++) {
			std::cout << "Should the bot type a message after click " << i << "? [y / n]: ";
			GetInput(ch, "");
			if(ch == 'n' || ch == 'N') tmp.SetTypeAfterClick(false, i);
			else  {
				tmp.SetTypeAfterClick(true, i);
				numMsgs++;
			}
		}
	}
	
	//Get the number of messages to type:
	if(numMsgs == 0) {
		//Ask for number of messages
		GetInput(numMsgs, "Enter the number of messages this bot should type: ", 0);
	}
	tmp.SetNumMsgs(numMsgs);
	
	if(numMsgs > 0) {
		//Get the messages
		for(i = 0; i < numMsgs; i++) {
			std::cout << "Type message " << i << " (end with a semicolon): ";
			std::getline(std::cin, stmp, ';');
			tmp.SetMsg(stmp, i);
		}
		
		//Get wait times for messages
		for(i = 0; i < numMsgs; i++) {
			std::cout << "How long should the bot wait after typing message " << i << "?: ";
			GetInput(itmp, "", 0);
			tmp.SetTypeTime(itmp, i);
		}
		
		//Get enter after click members
		for(i = 0; i < numMsgs; i++) {
			std::cout << "Should the bot press enter after message " << i << "? [y / n]: ";
			GetInput(ch, "");
			if(ch == 'n' || ch == 'N') tmp.SetEnterAfterType(false, i);
			else tmp.SetEnterAfterType(true, i);
		}
		
	}
	
	GetInput(itmp, "How many times should the bot repeat these actions?: ");
	tmp.SetRepeat(itmp);
	
	//Write the file.
	fout << tmp;
	fout.close();
	
	return true;
	
}

//Function: CheckBotMenu
//Purpose: Menu for showing bot values
//Return false when the user wants to return 
bool CheckBotMenu() {
	
	std::cout << "Check values for bot: " << botName << std::endl << std::endl
		<< "1) Number of Clicks" << std::endl
		<< "2) Coordinates" << std::endl
		<< "3) Click Times" << std::endl
		<< "4) Type After Click" << std::endl
		<< "5) Number of Messages" << std::endl
		<< "6) Messages" << std::endl
		<< "7) Message Times" << std::endl
		<< "8) Enter After Type" << std::endl
		<< "9) Repeat" << std::endl
		<< "0) Return to main menu" << std::endl << std::endl;
		
	int selection;
	GetInput(selection, "Enter a selection: ");
	
	std::cout << "\x1B[2J\x1B[H";
	
	int i;
	switch(selection) {
		case 1:
			std::cout << "Number of clicks: " << bot->GetNumClicks() << std::endl;
			break;
		case 2:
			std::cout << "Coordinates: " << std::endl;
			for(i = 0; i < bot->GetNumClicks(); i++) {
				POINT p = bot->GetPoint(i);
				std::cout << "( " << p.x << ", " << p.y << " )" << std::endl;	
			}
			break;
		case 3:
			std::cout << "Click times: " << std::endl;
			for(i = 0; i < bot->GetNumClicks(); i++) {
				std::cout << "Wait " << bot->GetClickTime(i) << " seconds after click " << i << std::endl;	
			}
			break;
		case 4:
			std::cout << "Type after click? " << std::endl;
			for(i = 0; i < bot->GetNumClicks(); i++) {
				std::cout << "Type after click " << i << "? -> " << std::boolalpha << bot->GetTypeAfterClick(i) << std::endl;
			}
			break;
		case 5:
			std::cout << "Number of messages: " << bot->GetNumMsgs() << std::endl;
			break;
		case 6:
			std::cout << "Messages: " << std::endl;
			for(i = 0; i < bot->GetNumMsgs(); i++) {
				std::cout << "Message " << i << ": " << bot->GetMsg(i) << std::endl << std::endl;	
			}
			break;
		case 7:
			std::cout << "Message times: " << std::endl;
			for(i = 0; i < bot->GetNumMsgs(); i++) {
				std::cout << "Wait " << bot->GetTypeTime(i) << " seconds after typing message " << i << std::endl;
			}	
			break;
		case 8:
			std::cout << "Press enter after message?" << std::endl;
			for(i = 0; i < bot->GetNumMsgs(); i++) {
				std::cout << "Press enter after message " << i << "? -> " << bot->GetEnterAfterType(i) << std::endl;	
			}
			break;
		case 9:
			if(bot->GetRepeat() == 0) {
				std::cout << "Repeat bot infinite times" << std::endl;
				break;
			}
			std::cout << "Repeat bot " << bot->GetRepeat() << " times." << std::endl;
			break;
		case 0:
			return false;
			break;
		default:
			std::cout << "Unrecognized input: " << selection << std::endl;
			break;
	}
	
	return true;	
	
}

//Function: SetBotMenu
//Purpose: Menu for checking bot values
//Return false when user wants to return
bool SetBotMenu() {
	
	std::cout << "Check values for bot: " << botName << std::endl << std::endl
		<< "1) Number of Clicks" << std::endl
		<< "2) Coordinates" << std::endl
		<< "3) Click Times" << std::endl
		<< "4) Type After Click" << std::endl
		<< "5) Number of Messages" << std::endl
		<< "6) Messages" << std::endl
		<< "7) Message Times" << std::endl
		<< "8) Enter After Type" << std::endl
		<< "9) Repeat" << std::endl
		<< "0) Return to main menu" << std::endl << std::endl;
		
	int selection;
	GetInput(selection, "Enter a selection: ");
	
	std::cout << "\x1B[2J\x1B[H";
	
	int i, tmp;
	bool btmp;
	POINT ptmp;
	std::string stmp;
	switch(selection) {
		case 1:
			std::cout << "Enter a new number of clicks: ";
			std::cin >> tmp;
			bot->SetNumClicks(tmp);
			break;
		case 2:
			std::cout << "Enter an index to change: 0 to " << (bot->GetNumClicks() - 1) << ": ";
			std::cin >> i;
			std::cout << "Enter an x y coordinate pair: ";
			std::cin >> ptmp.x >> ptmp.y;
			bot->SetPoint(ptmp, i);
			break;
		case 3:
			std::cout << "Enter an index to change: 0 to " << (bot->GetNumClicks() - 1) << ": ";
			std::cin >> i;
			std::cout << "Enter a new wait time: ";
			std::cin >> tmp;
			bot->SetClickTime(tmp, i);
			break;
		case 4:
			std::cout << "Enter an index to change: 0 to " << (bot->GetNumClicks() - 1) << ": ";
			std::cin >> i;
			std::cout << "Enter a new value (0, 1): ";
			std::cin >> btmp;
			bot->SetTypeAfterClick(btmp, i);
			break;
		case 5:
			std::cout << "Enter a new number of messages: ";
			std::cin >> tmp;
			bot->SetNumMsgs(tmp);
			break;
		case 6:
			std::cout << "Enter an index to change: 0 to " << (bot->GetNumMsgs() - 1) << ": ";
			std::cin >> i;
			std::cout << "Enter a new message (End with ;): " << std::endl;
			std::cin.ignore(1000, '\n');
			std::getline(std::cin, stmp, ';');
			bot->SetMsg(stmp, i);
			break;
		case 7:
			std::cout << "Enter an index to change: 0 to " << (bot->GetNumMsgs() - 1) << ": ";
			std::cin >> i;
			std::cout << "Enter a new wait time: ";
			std::cin >> tmp;
			bot->SetTypeTime(tmp, i);
			break;
		case 8:
			std::cout << "Enter an index to change: 0 to " << (bot->GetNumMsgs() - 1) << ": ";
			std::cin >> i;
			std::cout << "Enter a new value (0, 1): ";
			std::cin >> btmp;
			bot->SetEnterAfterType(btmp, i);
			break;
		case 9:
			std::cout << "Enter a new repeat value (0 for forever): ";
			std::cin >> tmp;
			bot->SetRepeat(tmp);
			break;
		case 0:
			return false;
			break;
		default:
			std::cout << "Unrecognized input: " << selection << std::endl;
			break;
	}
	
	return true;
	
}