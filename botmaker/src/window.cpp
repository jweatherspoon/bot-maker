#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "headers/window.h"

std::ostream &operator<<(std::ostream &out, const POINT &rhs) {
	out << rhs.x << " " << rhs.y;
	return out;
}

//Get the coordinates of the mouse cursor
void GetCursorPos(POINT &p) {
	Display *dpy; 
	Window wRoot, wReturn;
	int wX, wY;
	unsigned int mask;
	
	dpy = XOpenDisplay(0);
	wRoot = XRootWindow(dpy, 0);
	
	XQueryPointer(dpy, wRoot, &wReturn, &wReturn, &p.x, &p.y, &wX, &wY, &mask);
	
	XCloseDisplay(dpy);
}

//Move the mouse cursor to a point.
void SetCursorPos(POINT p) {
	Display *dpy;
	Window rootWindow;
	
	dpy = XOpenDisplay(0);
	rootWindow = XRootWindow(dpy, 0);
	
	XSelectInput(dpy, rootWindow, KeyReleaseMask);
	
	XWarpPointer(dpy, None, rootWindow, 0, 0, 0, 0, p.x, p.y);
	
	XFlush(dpy);
	
	XCloseDisplay(dpy);
}

//Click a point on the screen
void Click(POINT p, bool ret) {
	
	POINT before;
	if(ret) {
		GetCursorPos(before);
	}
	SetCursorPos(p);
	
	Click();
	
	if(ret)
		SetCursorPos(before);
}

//Click on the screen
void Click() {
	Display *dpy; 
	Window wRoot, wReturn;
	
	dpy = XOpenDisplay(0);
	wRoot = RootWindow(dpy, 0);
	
	XEvent event;
	
	event.type = ButtonPress;
	event.xbutton.button = Button1;
	event.xbutton.same_screen = true;
	
	XQueryPointer(dpy, wRoot, &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root,
				  &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	
	event.xbutton.subwindow = event.xbutton.window;
	
	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		
		XQueryPointer(dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}
	
	XSendEvent(dpy, event.xbutton.window, true, 0xFFF, &event);
	
	XFlush(dpy);
	
	usleep(100 * 1000);
	
	event.type = ButtonRelease;
	event.xbutton.state = (1L<<8); //Button1 mask
	
	XSendEvent(dpy, event.xbutton.window, true, 0xFFF, &event);
	
	XFlush(dpy);
	
	XCloseDisplay(dpy);
}

void Type(const char *msg) {
	while(*msg != '\0') {
		Type(*msg);
		msg++;
	}
}

void Type(char ch) {
	bool shift = false;
	if(ch >= 97 && ch <= 122) {
		ch -= 32;
		shift = true;
	}
	
	Display *dpy = XOpenDisplay(0);
	Window wRoot = RootWindow(dpy, 0);
	
	Window wFocus;
	int revert;
	XGetInputFocus(dpy, &wFocus, &revert);
	
	XEvent event;
	
	event.type = KeyPress;
	event.xkey.display = dpy;
	event.xkey.window = wFocus;
	event.xkey.root = wRoot;
	event.xkey.subwindow = None;
	event.xkey.time = CurrentTime;
	event.xkey.x = 1;
	event.xkey.y = 1;
	event.xkey.x_root = 1;
	event.xkey.y_root = 1;
	event.xkey.same_screen = true;
	event.xkey.keycode = XKeysymToKeycode(dpy, ch);
	event.xkey.state = 0;
	
	XSendEvent(dpy, wFocus, true, ch, &event);
	
	event.type = KeyRelease;
	
	XSendEvent(dpy, wFocus, true, ch, &event);
	
	XCloseDisplay(dpy);
	
}