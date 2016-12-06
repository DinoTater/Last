#include "ucode.c"
#include "helper.h"

int main(int argc, int argv[]) {
	char buf[RDSIZE], *infile, *outfile;
	int toFile = 0;
	int n = 0, i = 0;
	int ifd = STDIN;
	int ofd = STDOUT;

	if(argc == 3) {
		infile = argv[1];
		outfile = argv[2];
		ifd = open(infile, O_RDONLY);
		close(ofd);
		ofd = open(outfile, O_WRONLY | O_CREAT);

		if(ifd < 0) {
			close(ofd);
			gettty(buf);
			open(buf, O_WRONLY);
			printf("File does not exist.\n");
			exit(1);
		}

		if(ofd < 0) {
			close(ofd);
			gettty(buf);
			open(buf, O_WRONLY);
			printf("Could not open file).\n");
			exit(1);
		}
	}

	toFile = OutputRedirected();

	n = getLine(ifd, buf, RDSIZE);

	do {
		for(i = 0; buf[i] != 0; i++) {
			if(buf[i] == '\n' && !toFile) {
				putc('\r');
			}

			if(buf[i] >= 97) {
				buf[i] -= 32;
			}
			putc(buf[i]);
		}

		n = getLine(ifd, buf, RDSIZE);
	} while(strchr(buf, 4));
	close(ifd);
	close(ofd);
	exit(0);
}