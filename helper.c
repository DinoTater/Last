#include "helper.h"

int getLine(int fd, char *line, int length) {
	int i = 0, len = 0, n = 0;
	char lastc = 5;
	char temp[10];
	//char temp2[10];
	
	for(i=0;i<10;i++) { temp[i] = 0; }

	for(i = 0; (i < length) && (lastc != '\n') && (lastc != '\r') && (lastc != 174) && (lastc > 4); i++) {
		read(fd, temp, 1);
		lastc = temp[0];
		//n = sprintf(temp2, "%d", lastc);
		//write(2, temp2, n);
		if(lastc == 0) {
			//write(2, "lastc == 0\n\r", 12);
			*(line+i) = 4;
			*(line+i+1) = 0;
			return -1;
		}
		*(line+i) = lastc;
	}
	if(lastc == 4) { i++; /*write(2, "lastc == 4\n\r", 12);*/ }
	*(line+i) = 0;
	len = strlen(line);
	return len;
}

void cpystr(char *dest, char *src) {
	char *ap = dest, *bp = src;

	while(*bp != 0) {
		*ap = *bp; //copy over
		ap++;bp++;
	}
}

int OutputRedirected() {
	STAT *stat = (STAT*)malloc(sizeof(stat));
	int n = 0;
	char buf[32];

	//get stat
	fstat(STDOUT, stat);

	//n = sprintf(buf, "mode: %x or %x. Isreg? %d\n\r", stat->st_mode, (stat->st_mode & 0xF000), S_ISREG(stat));
	write(2, buf, n);

	if (((stat->st_mode & 0xF000) == 0x8000) || 
		((stat->st_mode & 0xF000) == 0x4000) ||
		((stat->st_mode & 0xF000) == 0xA000)) {
		//printf("Output Redirected\n");
		//getc();
		return 1;
	}

	return 0;
}

int InputRedirected() {
	STAT *stat = (STAT*)malloc(sizeof(stat));

	//get stat
	fstat(STDIN, stat);

	if (((stat->st_mode & 0xF000) == 0x8000) || 
		((stat->st_mode & 0xF000) == 0x4000) ||
		((stat->st_mode & 0xF000) == 0xA000)) {
		return 1;
	}

	return 0;
}

void printStr(char *str, int redirected) {
	int i = 0;
	
	for(; i < strlen(str); i++) {
		if(redirected && str[i] == '\n') {
			putc('\r');
		}
		putc(str[i]);
	}
}

int S_ISDIR(STAT *stat) {
	return (((stat->st_mode) & TYPEBITS) == DIR);
}

int S_ISREG(STAT *stat) {
	return (((stat->st_mode) & TYPEBITS) == REG);
}

int S_ISLNK(STAT *stat) {
	return (((stat->st_mode) & TYPEBITS) == LNK);
}

void basename(char *path, char *bname) {
	int  i = 0, lastSlash = 0;
	int pathLen = strlen(path);
	char *pp = path, *bp = bname;
	for(; i < pathLen; i++) {
		if(*pp == '/') {
			lastSlash = i;
		}
		pp++;
	}

	pp = path;
	for(i = 0; i < lastSlash; i++) {
		*bp = *pp;
		bp++; pp++;
	}

	*bp = 0;
}

void dirname(char *path, char *dname) {
	int i = 0, dnamelen = 0;
	int pathlen = strlen(path);
	char *pp, *dp = dname;
	pp = path + pathlen - 1;
	
	//find last slash
	for(; (pp >= path) && (*pp != '/' ); pp--);

	for(pp++; pp < (path + pathlen); pp++) {
		*dp = *pp;
		dp++;
	}
	*dp = 0;
}