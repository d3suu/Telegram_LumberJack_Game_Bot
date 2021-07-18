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
	//int Y = 676;
	int Yover = 660;
	int Ydown = 680;

	rgbColor galazPrawo, galazLewo;
	
	int galazPoLewej(){
		for(int Y = Yover; Y<=Ydown; Y++){
			galazLewo = getPixelColor(galazLewoX,Y,d);
			if(galazLewo.g == 0x74) return 1;
		}
		return 0;
	}
	int galazPoPrawej(){
		for(int Y = Yover; Y<=Ydown; Y++){
			galazPrawo = getPixelColor(galazPrawoX,Y,d);
			if(galazPrawo.g == 0x74) return 1;
		}
		return 0;
	}

	while(1){

		// zaczekaj na galaz w miejscu
		printf("Czekam na galaz...\n");
		while(!galazPoLewej() && !galazPoPrawej()){
			/*
			// sprawdz czy zablokowany
			galazPrawo = getPixelColor(galazPrawoX,Y-50,d);
			galazLewo = getPixelColor(galazLewoX,Y-50,d);
			if(galazPrawo.g == 0x74 || galazLewo.g == 0x74){
				printf("Zablokowany...\n");
				pressRight();
				usleep(1000);
			}
			*/
			continue;
		}
		
		// dokonaj akcji
		if(galazPoPrawej()){
			printf("Galaz po prawej stronie\n");
			pressLeft();
			usleep(100);
			pressLeft();
		}else if(galazPoLewej()){
			printf("Galaz po lewej stronie\n");
			pressRight();
			usleep(100);
			pressRight();
		}

		// zaczekaj az drzewo opadnie
		/*
		printf("Czekam az opadnie...\n");
		while(galazPoPrawej() || galazPoLewej()){
			continue;
		}
		*/
	}

	return 0;
}
