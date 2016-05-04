#include <iostream>
#include <string>
#include <X11/keysymdef.h>
#include <unistd.h>
#include "headers/bot.h"
#include "headers/window.h"

void Sleep(int);

Bot::Bot(int nc, POINT *ps, int *ct, bool *tac, int nm, std::string *ms, int *tt, bool *eat, int r) {
	int i;
	
	numClicks = (nc > 0) ? nc : 0;
	
	if(numClicks > 0) {
		points = new POINT[numClicks];
		for(i = 0; i < numClicks; i++) {
			points[i].x = (ps) ? ps[i].x : 0;
			points[i].y = (ps) ? ps[i].y : 0;
		}
		
		clickTimes = new int[numClicks];
		for(i = 0; i < numClicks; i++) 
			clickTimes[i] = (ct) ? ct[i] : 1;

		typeAfterClick = new bool[numClicks];
		for(i = 0; i < numClicks; i++) 
			typeAfterClick[i] = (tac) ? tac[i] : false;
	
	} else {
		points = NULL;
		typeAfterClick = NULL;
	}
	
	numMsgs = (nm > 0) ? nm : 0;
	
	if(numMsgs > 0) {
		msgs = new std::string[nm];
		for(i = 0; i < numMsgs; i++)
			msgs[i] = (ms) ? ms[i] : "";
		
		typeTimes = new int[numMsgs];
		for(i = 0; i < numMsgs; i++)
			typeTimes[i] = (tt) ? tt[i] : 1;

		enterAfterType = new bool[numMsgs];
		for(i = 0; i < numMsgs; i++) 
			enterAfterType[i] = (eat) ? eat[i] : false;
	} else {
		msgs = NULL;
		enterAfterType = NULL;
	}
	
	repeat = (r > 0) ? r : 0;
}

Bot::Bot(const Bot &copy) {
	int i;
	
	numClicks = copy.numClicks;
	
	if(numClicks > 0) {
		points = new POINT[numClicks];
		for(i = 0; i < numClicks; i++) {
			points[i].x = copy.points[i].x;	
			points[i].y = copy.points[i].y;
		}

		typeAfterClick = new bool[numClicks];
		for(i = 0; i < numClicks; i++) 
			typeAfterClick[i] = copy.typeAfterClick[i];
	} else {
		points = NULL;
		typeAfterClick = NULL;
	}
	
	numMsgs = copy.numMsgs;
	
	if(numMsgs > 0) {
		msgs = new std::string[numMsgs];
		for(i = 0; i < numMsgs; i++) 
			msgs[i] = copy.msgs[i];
		
		enterAfterType = new bool[numMsgs];
		for(i = 0; i < numMsgs; i++) 
			enterAfterType[i] = copy.enterAfterType[i];
	} else {
		msgs = NULL;
		enterAfterType = NULL;
	}
	
	repeat = copy.repeat;
}

Bot::~Bot() {
	
	numClicks = 0;
	
	if(points) {
		delete[] points;
		points = NULL;
	}
	
	if(clickTimes) {
		delete[] clickTimes;
		clickTimes = NULL;
	}
	
	if(typeAfterClick) {
		delete[] typeAfterClick;
		typeAfterClick = NULL;
	}
	
	numMsgs = 0;
	
	if(msgs) {
		delete[] msgs;
		msgs = NULL;
	}
	
	if(typeTimes) {
		delete[] typeTimes;
		typeTimes = NULL;
	}
	
	if(enterAfterType) {
		delete[] enterAfterType;
		enterAfterType = NULL;
	}
	
	repeat = false;
	
}

int Bot::GetNumClicks() const {
	return numClicks;
}

void Bot::SetNumClicks(int nc) {
	if(nc == numClicks) return;
	
	if(nc > 0) {
		int i;
		
		POINT *pTmp = new POINT[nc];
		for(i = 0; i < numClicks; i++) {
			pTmp[i].x = points[i].x;
			pTmp[i].y = points[i].y;
		}
		delete[] points;
		points = pTmp;
		pTmp = NULL;
		
		
		
		numClicks = nc;
	} else {
		numClicks = 0;
		if(points) {
			delete[] points;
			points = NULL;
		}
		if(clickTimes) {
			delete[] clickTimes;
			clickTimes = NULL;
		}
		if(typeAfterClick) {
			delete[] typeAfterClick;
			typeAfterClick = NULL;
		}
	}
	
}

POINT Bot::GetPoint(int index) const {
	if(index > 0 && index < numClicks) 
		return points[index];
	
	POINT p;
	p.x = 0, p.y = 0;
	return p;
}

void Bot::SetPoint(POINT p, int index) {
	if(index < 0 || index >= numClicks) return;
	
	points[index].x = p.x;
	points[index].y = p.y;
}

int Bot::GetClickTime(int index) const {
	if(index < 0 || index >= numClicks) return -1;
	
	return clickTimes[index];
}

void Bot::SetClickTime(int sec, int index) {
	if(index < 0 || index >= numClicks) return;
	
	if(sec < 0) sec = 0;
	
	clickTimes[index] = sec;
}

bool Bot::GetTypeAfterClick(int index) const {
	if(index < 0 || index >= numClicks) return false;
	
	return typeAfterClick[index];
}

void Bot::SetTypeAfterClick(bool val, int index) {
	if(index < 0 || index >= numClicks) return;
	
	typeAfterClick[index] = val;
}

int Bot::GetNumMsgs() const {
	return numMsgs;
}

void Bot::SetNumMsgs(int nm) {
	if(nm == numMsgs) return;
	
	if(nm > 0) {
		
		int i;
		
		if(msgs) {
			std::string *mtmp = new std::string[nm]();
			for(i = 0; i < ((numMsgs > nm) ? nm : numMsgs); i++) {
				mtmp[i] = msgs[i];
			}
			delete[] msgs;
			msgs = mtmp;
		}
		
		if(typeTimes) {
			int *ttmp = new int[nm]();
			for(i = 0; i < ((numMsgs > nm) ? nm : numMsgs); i++) {
				ttmp[i] = typeTimes[i];
			}
			delete[] typeTimes;
			typeTimes = ttmp;
		}
		
		if(enterAfterType) {
			bool *btmp = new bool[nm]();
			for(i = 0; i < ((numMsgs > nm) ? nm : numMsgs); i++) {
				btmp[i] = enterAfterType[i];
			}
			delete[] enterAfterType;
			enterAfterType = btmp;
		}
		
		numMsgs = nm;
		
	} else {
		numMsgs = 0;
		
		if(msgs) {
			delete[] msgs;
			msgs = NULL;
		}
		
		if(typeTimes) {
			delete[] typeTimes;
			typeTimes = NULL;
		}
		
		if(enterAfterType) {
			delete[] enterAfterType;
			enterAfterType = NULL;
		}
	}
}

std::string Bot::GetMsg(int index) const {
	if(index < 0 || index >= numMsgs) return "";
	
	return msgs[index];
}

void Bot::SetMsg(std::string m, int index) {
	if(index < 0 || index >= numClicks) return;
	
	msgs[index] = m;
}

int Bot::GetTypeTime(int index) const {
	if(index < 0 || index >= numClicks) return -1;
	
	return typeTimes[index];
}

void Bot::SetTypeTime(int sec, int index) {
	if(index < 0 || index >= numClicks) return;
	
	if(sec < 0) sec = 0;
	
	typeTimes[index] = sec;
}

bool Bot::GetEnterAfterType(int index) const {
	if(index < 0 || index >= numMsgs) return false;
	
	return enterAfterType[index];
}

void Bot::SetEnterAfterType(bool val, int index) {
	if(index < 0 || index >= numMsgs) return;
	
	enterAfterType[index] = val;
}

int Bot::GetRepeat() const {
	return repeat;
}

void Bot::SetRepeat(int r) {
	repeat = (r > 0) ? r : 0; //0 means loop forever.
}

//Function: Bot::StartBot
//Purpose: Start the bot's operation
//Note: If repeat is set to 0, the loop will continue forever
void Bot::StartBot() const {
	int count = 0;
	while(true) {
		
		int i, j = 0;
		for(i = 0; i < numClicks; i++) {
			Click(points[i], false);
			Sleep(clickTimes[i]);
			
			//Type that shit yo
			if(typeAfterClick[i]) {
				Type(msgs[j].c_str());
				if(enterAfterType[j]) {
					usleep(100 * 1000);
					Type(0x0D); //Return
				}
				Sleep(typeTimes[j++]);
			}
		}
		
		//Break out of the loop if it shouldn't loop forever
		if(repeat > 0) 
			if(++count >= repeat) break;
	}
}

//Function: operator<<
//Purpose: output a bot object
//Parameters:
//	std::ostream &out: The ostream to output to
//	const bot &rhs: The bot to output
//Returns out to allow for chaining
std::ostream &operator<<(std::ostream &out, const Bot &rhs) {
	
	int i;
	
	//Output number of clicks
	out << rhs.numClicks << std::endl;
	
	//Output coordinates to click
	for(i = 0; i < rhs.numClicks; i++) 
		out << rhs.points[i] << std::endl;	
	
	//Output time after each click
	for(i = 0; i < rhs.numClicks; i++) 
		out << rhs.clickTimes[i] << " ";
	
	out << std::endl;
	
	//Output "should bot type after this click"
	for(i = 0; i < rhs.numClicks; i++) 
		out << rhs.typeAfterClick[i] << " ";
	
	//Output number of messages
	out << std::endl << rhs.numMsgs << std::endl;
	
	//Output messages
	for(i = 0; i < rhs.numMsgs; i++) 
		out << rhs.msgs[i] << ';' << std::endl;
	
	//Output time to wait after typing
	for(i = 0; i < rhs.numMsgs; i++) 
		out << rhs.typeTimes[i] << " ";
	
	out << std::endl;
	
	//Output "Should bot press enter after typing"
	for(i = 0; i < rhs.numMsgs; i++)
		out << rhs.enterAfterType[i] << " ";
	
	//Output repeat status
	out << std::endl << rhs.repeat;
	
	return out;
}

//Function: operator>>
//Purpose: Read in a bot object 
//Parameters:
//	std::istream &in: The input stream to read from
//	Bot &rhs: The bot to read into
//Returns in to allow for chaining
std::istream &operator>>(std::istream &in, Bot &rhs) {
	int i;
	
	//Get numclicks
	in >> rhs.numClicks;
	
	//Delete / reallocate and get coordinates
	if(rhs.points) 
		delete[] rhs.points;
	rhs.points = new POINT[rhs.numClicks];
	
	for(i = 0; i < rhs.numClicks; i++) {
		in >> rhs.points[i].x >> rhs.points[i].y;
	}
	
	//Delete / reallocate and get click times
	if(rhs.clickTimes) 
		delete[] rhs.clickTimes;
	rhs.clickTimes = new int[rhs.numClicks];
	
	for(i = 0; i < rhs.numClicks; i++) 
		in >> rhs.clickTimes[i];
	
	//delete / reallocate and get type after click values
	if(rhs.typeAfterClick) 
		delete[] rhs.typeAfterClick;
	rhs.typeAfterClick = new bool[rhs.numClicks];
	
	for(i = 0; i < rhs.numClicks; i++) {
		in >> rhs.typeAfterClick[i];
	}
	
	//Get number of messages
	in >> rhs.numMsgs;
	
	//delete / reallocate and get messages
	if(rhs.msgs) 
		delete[] rhs.msgs;
	rhs.msgs = new std::string[rhs.numMsgs];
	
	for(i = 0; i < rhs.numMsgs; i++) {
		in.get();
		std::getline(in, rhs.msgs[i], ';');
	}
	
	//delete / reallocate and get type times
	if(rhs.typeTimes) 
		delete[] rhs.typeTimes;
	rhs.typeTimes = new int[rhs.numMsgs];
	
	for(i = 0; i < rhs.numMsgs; i++) 
		in >> rhs.typeTimes[i];
	
	//delete / reallocate and get enter after type values
	if(rhs.enterAfterType)
		delete[] rhs.enterAfterType;
	rhs.enterAfterType = new bool[rhs.numMsgs];
	
	for(i = 0; i < rhs.numMsgs; i++) {
		in >> rhs.enterAfterType[i];
	}
	
	//get repeat value
	in >> rhs.repeat;
	
	return in;
}

void Sleep(int seconds) {
	usleep(seconds * 1000 * 1000);	
}