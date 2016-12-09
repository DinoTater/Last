#include "ucode.c"
#include "helper.c"

int main(int argc, int *argv[]) {
	char *pattern, *file, buf[RDSIZE];
	int fd = STDIN, n = 0, i = 0, j = 0, toFile = 0;

	if(argc < 2) {
		printf("grep usage: grep pattern [filename]\n");
		exit(1);
	}
	else if(argc == 2) {
		pattern = argv[1];
		fd = 0;
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
		
		if(strstr(buf, pattern)) {
			printf("%s\n", buf);
			if(fd == 0) {
				putc('\r');
			}
		}
	}

	close(fd);
	exit(0);
}