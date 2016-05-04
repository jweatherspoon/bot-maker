#ifndef BOT_H
#define BOT_H

#include <iostream>
#include "window.h"

class Bot {
public:
	Bot(int = 0, POINT * = NULL, int * = NULL, bool * = NULL, int = 0, std::string * = NULL, int * = NULL, bool * = NULL, int = 0);
	Bot(const Bot &);
	~Bot();
	
	int GetNumClicks() const;
	void SetNumClicks(int);
	
	POINT GetPoint(int) const;
	void SetPoint(POINT, int);
	
	int GetClickTime(int) const;
	void SetClickTime(int, int);
	
	bool GetTypeAfterClick(int) const;
	void SetTypeAfterClick(bool, int);
	
	int GetNumMsgs() const;
	void SetNumMsgs(int);
	
	std::string GetMsg(int) const;
	void SetMsg(std::string, int);
	
	int GetTypeTime(int) const;
	void SetTypeTime(int, int);
	
	bool GetEnterAfterType(int) const;
	void SetEnterAfterType(bool, int);
	
	int GetRepeat() const;
	void SetRepeat(int);
	
	void StartBot() const;
	
	friend std::ostream &operator<<(std::ostream &, const Bot &);
	friend std::istream &operator>>(std::istream &, Bot &);
	
private:
	int numClicks; //Number of times the bot should click
	POINT *points; //Contains coordinates to click
	int *clickTimes; //Seconds to wait after clicking
	
	bool *typeAfterClick; //Determines if the bot should type after a certain click
	
	int numMsgs; //Number of things the bot should type
	std::string *msgs; //Messages to type
	int *typeTimes; //seconds to wait after typing
	
	bool *enterAfterType; //Determines if the bot should press enter after typing
	
	int repeat; //True if the bot should loop
};

#endif