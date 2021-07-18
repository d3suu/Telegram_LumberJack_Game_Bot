#include <stdio.h>

// Dumps events from keyboard
// 8 byte - sec
// 8 byte - usec
// 2 byte - type
// 2 byte - code
// 4 byte - value

int main(){

	//FILE* f = fopen("./eventdump","rb");
	FILE* f = fopen("/dev/input/event4","rb");
	unsigned long sec, usec;
	unsigned short type, code;
	unsigned int value;
	while(1){
		fread(&sec,8,1,f);
		fread(&usec,8,1,f);
		fread(&type,2,1,f);
		fread(&code,2,1,f);
		fread(&value,4,1,f);
		printf("%.16X %.16X %.4X %.4X %.8X\n", sec, usec, type, code, value);
		if(feof(f)){
			break;
		}
	}
	return 0;
}
