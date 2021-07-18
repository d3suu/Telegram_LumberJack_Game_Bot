#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "keyboard.h"

typedef struct rgbColor {
	char r;
	char g;
	char b;
} rgbColor;

rgbColor getPixelColor(int x, int y, Display* d){
	XColor c;
	//Display* d = XOpenDisplay((char *) NULL);
	Screen* s = XDefaultScreen(d);
	//int x=200;
	//int y=200;

	XImage* image;
	image = XGetImage(d, XRootWindow(d, s), x, y, 1, 1, AllPlanes, XYPixmap);
	c.pixel = XGetPixel(image, 0, 0);
	XFree(image);
	XQueryColor(d, XDefaultColormap(d, s), &c);
	//printf("%x %x %x\n", c.red/256, c.green/256, c.blue/256);

	rgbColor this;
	this.r = c.red/256;
	this.g = c.green/256;
	this.b = c.blue/256;
	return this;
}

int main(){
	printf("RUN ME AS ROOT/SUDO\n");

	Display* d = XOpenDisplay((char *) NULL);

	int galazPrawoX = 1485;
	int galazLewoX = 1430;
	int Y = 676;

	rgbColor galazPrawo, galazLewo;
	int czekajCounter = 0;

	while(1){
		// zaczekaj na galaz w miejscu
		while(galazPrawo.g != 0x74 && galazLewo.g != 0x74){
			printf("Czekam na galaz...\n");
			galazPrawo = getPixelColor(galazPrawoX,Y,d);
			galazLewo = getPixelColor(galazLewoX,Y,d);
			czekajCounter++;
			if(czekajCounter == 10){
				// Zgubiles krok?
				printf("Zgubilem krok\n");
				pressRight();
				czekajCounter = 0;
			}
			usleep(10000);
		}
		
		// dokonaj akcji
		if(galazPrawo.g == 0x74){
			printf("Galaz po prawej stronie\n");
			pressLeft();
			usleep(10000);
			pressLeft();
		}else if(galazLewo.g == 0x74){
			printf("Galaz po lewej stronie\n");
			pressRight();
			usleep(10000);
			pressRight();
		}

		// zaczekaj az drzewo opadnie
		while(galazPrawo.g == 0x74 || galazLewo.g == 0x74){
			printf("Czekam az opadnie...\n");
			galazPrawo = getPixelColor(galazPrawoX,Y,d);
			galazLewo = getPixelColor(galazLewoX,Y,d);
			usleep(10000);
		}

		// Zgubiles krok?
		if(galazPrawo.g != 0x74 && galazLewo.g != 0x74){
		}
	}

	return 0;
}
