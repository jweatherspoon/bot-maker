#ifndef WINDOW_H
#define WINDOW_H

struct POINT {
	int x;
	int y;
	
	friend std::ostream &operator<<(std::ostream &, const POINT &);
};

void GetCursorPos(POINT &);
void SetCursorPos(POINT);

void Click(POINT, bool);
void Click();

void Type(const char *);
void Type(char);

#endif