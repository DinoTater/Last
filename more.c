// 'more' as in Unix
// filename optional

#define ROWS 20
#define COLUMNS 80

int main(int argc, char *argv[])
{
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
					pringLines(fd, ROWS);
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