#include "ucode.c"
#include "helper.h"

void copyFileToFile(char *src, char *dest);

char *cat = "cat";

int main(int argc, char *argv[]) {
	char *src, *dest;
	STAT *srcStat, *destStat;
	int srcDir, destDir;

	printf("CP YOU BASTARD!\n");

	if(argc < 3) {
		printf("ERROR: Usage: cp <src> <dest>\n");
		exit(1);
	}

	src = argv[1];
	dest = argv[2];
	if(argv[3]) {
		cat = argv[3];
	}
	stat(src, srcStat);
	stat(dest, destStat);

	srcDir = S_ISDIR(srcStat);
	destDir = S_ISDIR(destStat);

	copyFileToFile(src, dest);

	exit(0);
}

void copyFileToFile(char *src, char *dest) {
	int rd = 1024;
	int pid = 0, r = 0, in = 0, out = 0, n = 0;
	char buf[1024];
	pid = fork();

	if(pid) {
		wait(&r);
		if(r != 0)
			printf("Copying failed\n");
	}
	else {
		printf("%s -> %s\n", src, dest);
		close(STDIN);
		close(STDOUT);
		in = open(src, O_RDONLY);
		out = open(dest, O_WRONLY | O_TRUNC | O_CREAT);
		if (in >= 0 && out >= 0) {
			while (n = read(in, buf, rd)) {
				write(out, buf, n);
			}
			exit(0);
		}
		else
			exit(9);
	}

	return;
}