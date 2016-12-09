#include "helper.h"

int getLine(int fd, char *line, int length) {
	int i = 0, len = 0, n = 0;
	char lastc = 5;
	char temp[10];
	
	for(i=0;i<10;i++) { temp[i] = 0; }

	for(i = 0; (i < length) && (lastc != '\n') && (lastc != '\r') && (lastc != 174) && (lastc > 4); i++) {
		read(fd, temp, 1);
		lastc = temp[0];
		if(lastc == 0) {
			*(line+i) = 4;
			*(line+i+1) = 0;
			return -1;
		}
		*(line+i) = lastc;
	}
	if(lastc == 4) { i++; }
	*(line+i) = 0;
	len = strlen(line);
	return len;
}

int readLine(int input, char *inbuf) {
	int LRead, i = 0;
	char c;
	while(1) {
		LRead = read(input, &c, 1);
		if(LRead == 0)
			return 0;
		if(c == '\n' || c == '\r') {
			inbuf[i++] = '\n';
			return i;
		}
		else
			inbuf[i++] = c;
	}
}

void cpystr(char *dest, char *src) {
	char *ap = dest, *bp = src;

	while(*bp != 0) {
		*ap = *bp; //copy over
		ap++;bp++;
	}
}

