#include "helper.c"
#include "ucode.c"

int fd;
void quit();

int main(int argc, int *argv[]) {
	char c, lc = 0, buf[1024], temp[128], *tty;
	int i = 0, j = 0, n;
	int stdin, stdout, ttyout;

	stdin = 0;
	stdout = 1;
	gettty(tty);
	ttyout = open(tty, O_WRONLY);

	//read from stdin
	if(argc == 1) {
		fd = 0;
	}

	if (argc > 1) {
		for(j = 1; j < argc; j++) {
			fd = open(argv[j], O_RDONLY);
			if(fd < 0) {
				printf("Cannot find file %s\n", argv[j]);
				exit(1);
			}
			while(n = read(fd, buf, 1024)) {
				for (i = 0; i < n; i++) {
					write(stdout, buf + i, 1);
					if(buf[i] == '\n')
						write(ttyout, "\r", 1);
				}
			}
			close(stdin);
		}
	}
	else {
		while(read(0, &c, 1)) {
			if(c == '\n') {
				write(ttyout, "\r", 1);
				write(stdout, "\n", 1);
			}
			else if(c == '\r') {
				write(ttyout, "\r", 1);
				buf[i] = '\n';
				c = '\n';
				write(stdout, &c, 1);
				write(ttyout, buf, strlen(buf));
				write(ttyout, "\r", 1);
				bzero(buf, 1024);
				i = 0;
			}
			else {
				buf[i] = c;
				write(stdout, &c, 1);
				i++;
			}
		}
	}

	close(ttyout);
	exit(1);
}
