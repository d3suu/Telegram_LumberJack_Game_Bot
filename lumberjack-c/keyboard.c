#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>

#include "keyboard.h"

#define EV_PRESSED 1
#define EV_RELEASED 0
#define EV_REPEAT 2

void pressLeft(){
/*
0000000060F378C9 0000000000080617 0004 0004 000000CB
0000000060F378C9 0000000000080617 0001 0069 00000001
0000000060F378C9 0000000000080617 0000 0000 00000000
0000000060F378C9 0000000000093525 0004 0004 000000CB
0000000060F378C9 0000000000093525 0001 0069 00000000
0000000060F378C9 0000000000093525 0000 0000 00000000
*/
	int fd = 0;
	char *device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";

	// Write a key to the keyboard buffer
	if( (fd = open(device, O_RDWR)) > 0 )
	{
		struct input_event event;
		
		// Press a key (stuff the keyboard with a keypress)
			event.type = 0x0004;
			event.value = 0x000000CB;
			event.code = 0x0004;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0001;
			event.value = 0x00000001;
			event.code = 0x0069;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0000;
			event.value = 0x00000000;
			event.code = 0x0000;
			write(fd, &event, sizeof(struct input_event));
		
		// Release the key
			event.type = 0x0004;
			event.value = 0x000000CB;
			event.code = 0x0004;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0001;
			event.value = 0x00000000;
			event.code = 0x0069;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0000;
			event.value = 0x00000000;
			event.code = 0x0000;
			write(fd, &event, sizeof(struct input_event));
		close(fd);
	}
}

void pressRight(){
/*
0000000060F37907 000000000001421B 0004 0004 000000CD
0000000060F37907 000000000001421B 0001 006A 00000001
0000000060F37907 000000000001421B 0000 0000 00000000
0000000060F37907 0000000000028D9D 0004 0004 000000CD
0000000060F37907 0000000000028D9D 0001 006A 00000000
0000000060F37907 0000000000028D9D 0000 0000 00000000
*/
	int fd = 0;
	char *device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";

	// Write a key to the keyboard buffer
	if( (fd = open(device, O_RDWR)) > 0 )
	{
		struct input_event event;
		
		// Press a key (stuff the keyboard with a keypress)
			event.type = 0x0004;
			event.value = 0x000000CD;
			event.code = 0x0004;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0001;
			event.value = 0x00000001;
			event.code = 0x006A;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0000;
			event.value = 0x00000000;
			event.code = 0x0000;
			write(fd, &event, sizeof(struct input_event));
		
		// Release the key
			event.type = 0x0004;
			event.value = 0x000000CD;
			event.code = 0x0004;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0001;
			event.value = 0x00000000;
			event.code = 0x006A;
			write(fd, &event, sizeof(struct input_event));
			event.type = 0x0000;
			event.value = 0x00000000;
			event.code = 0x0000;
			write(fd, &event, sizeof(struct input_event));
		close(fd);
	}
}

