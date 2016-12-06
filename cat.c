#include "helper.h"
#include "ucode.c"

int fd;
void quit();

int main(int argc, int *argv[]) {
	char c, lc = 0;

	//read from stdin
	if(argc == 1)
		fd = 0;
	// from file
	else
		fd = open(argv[1], O_RDONLY);

	if(fd < 0) {
		printf("Cannot find file\n");
		exit(1);
	}

	while(read(fd, &c, 1) > 0) {
		putc(c);

		if (fd == 0) {
			if (c == '\n' && (lc != '\n' && lc != '\r'))
				putc('\r');
		}

		else {
			if (c == '\r' && (lc != '\n' && lc != '\r')) {
				putc('\n');
				putc('\r');
			}
		}

		lc = c;
	}

	quit();

	/*int i, n, toFile = 0, nbytes = 0;
	int inputRedirected();
	long bytes;
	char *file, buf[RDSIZE];
	char tbuf[32];
	STAT filestat;

	fd = STDIN;

	toFile = OutputRedirected();

	if(argc > 1) {
		file = argv[1];
		close(fd);
		fd = open(file, O_RDONLY);
		if(fd < 0) {
			printf("FILE: %s DOES NOT EXIST\n", file);
			exit(1);
		}
	}

	n = getLine(fd, buf, RDSIZE);
	do {
		for (i = 0; i < n; i++) {
			if(buf[i] == '\n') {
				if(!toFile) {
					printf("\n\r");
				}
				else if(buf[i] == 4) {
					quit();
				}
				else {
					printf("%c", '\n');
				}
			}
			else {
				printf("%c", buf[i]);
			}
		}
		n = getLine(fd, buf, RDSIZE);
	} while(!strchr(buf, 4));*/

	quit();
}

void quit(){
	close(fd);
	exit(0);
}