#include "ucode.c"
#include "helper.h"

int main(int argc, int *argv[]) {
	char *pattern, *file, buf[RDSIZE];
	int fd = STDIN, n = 0, i = 0, j = 0;

	// NEED TO DEAL WITH STDIN BIZNIZ

	if(argc < 2) {
		printf("grep usage: grep pattern [filename]\n");
		exit(1);
	}
	else if(argc == 2) {
		pattern = argv[1];
	}
	else if(argc == 3) {
		pattern = argv[1];
		file = argv[2];
		fd = open(file, O_RDONLY);
		if(fd < 0) {
			printf("File not found.\n");
			exit(1);
		}
	}

	while((n = getLine(fd, buf, RDSIZE)) > 0) {
		i = strstr(buf, pattern);
		if(i != NULL) {
			printf("%s\n", buf);
			if(!toFile) {
				putc('\r');
			}
		}
	}

	close(fd);
	exit(0);
}