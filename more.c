#include "ucode.c"
#include "helper.h"
	
// 'more' as in Unix
// filename optional

#define ROWS 20
#define COLUMNS 80

void printLines(int fd, int lines);

int main(int argc, char *argv[]) {
	char c, tty[64];
	int fd;

	// We using stdin?
	if (argc == 1)
	{
		fd = dup(0);
		close (0);
		gettty(tty);
		open(tty, O_RDONLY);
	}
	// Or not?
	else
	{
		fd = open(argv[1], O_RDONLY);
	}

	// We get anything?
	if (fd < 0)
	{
		printf("File not found\n");
		return -1;
	}

	while(1)
	{
		printLines(fd, ROWS);

		while(1)
		{
			// Get user command:
			c = getc();

			switch (c)
			{
				// Options: Enter/one line, space/pageDown, q/quit 
				case '\r':
				case '\n':
					printLines(fd, 1);
					break;
				case ' ':
					printLines(fd, ROWS);
					break;
				case 'q':
					putc('\n');
					return 0;
					break;
			}
		}
	}

	return 0;
}

// Prints 'lines' number of lines (Useful for printing a full page)
void printLines(int fd, int lines)
{
	int i, j, length;
	char c;

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			length = read(fd, &c, 1);
			putc(c);

			if(length < 1)
			{
				exit(0);
			}

			if (c == '\n' || c == '\r')
				break;
		}
	}

	putc('\n');
}




	/*int fd = STDIN, i = 0, toFile = 0, count = 24;
	int n = 0;
	char *file, buf[RDSIZE], input = 0;

	toFile = OutputRedirected();


	if(argc > 1) {
		file = argv[1];
		fd = open(file, O_RDONLY);
		if(fd < 0) {
			printf("File does not exist\n");
			exit(1);
		}
	}

	do {
		for(; (n = getLine(fd, buf, RDSIZE) > 0) && (count > 0); count--){
			printf("%s", buf);
			if(!toFile) {
				putc('\r');
			}
			if(strchr(buf, 4)) {
				quit(fd);
			}
		}

		if(n == 0) {
			count = 0;
		}

		input = getc();
		if(input == ' ') {
			count = 24;
		}
		else if (input > 0 && input < 255) {
			count = 1;
		}
	} while (count > 0);

	quit(fd);
}

void quit(int fd) {
	write(2, "Done with more\n\r", 16);
	close(fd);
	exit(0);
}*/