#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>

// Get keycodes with `xev`

void pressLeft(Display* dis){
	//Display *dis;
	//dis = XOpenDisplay(NULL);
	KeyCode modcode = 113; //XKeysymToKeycode(dis, XK_A);
	//XTestFakeKeyEvent(dis, modcode, False, 0);
	//XFlush(dis);
	XTestFakeKeyEvent(dis, modcode, True, 0);
	XFlush(dis);
	XTestFakeKeyEvent(dis, modcode, False, 0);
	XFlush(dis);
}
void pressRight(Display* dis){
	//Display *dis;
	//dis = XOpenDisplay(NULL);
	KeyCode modcode = 114;
	//XTestFakeKeyEvent(dis, modcode, False, 0);
	//XFlush(dis);
	XTestFakeKeyEvent(dis, modcode, True, 0);
	XFlush(dis);
	XTestFakeKeyEvent(dis, modcode, False, 0);
	XFlush(dis);
}
#ifdef keyboard2_main
int main(){
	sleep(5);

	Display *dis;
	dis = XOpenDisplay(NULL);
	KeyCode modcode = 0;
	modcode = 113; //XKeysymToKeycode(dis, XK_A);
	XTestFakeKeyEvent(dis, modcode, False, 0);
	XFlush(dis);
	XTestFakeKeyEvent(dis, modcode, True, 0);
	XFlush(dis);
	XTestFakeKeyEvent(dis, modcode, False, 0);
	XFlush(dis);

	return 0;
}
#endif
