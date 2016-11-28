// cat   [filename]         // cat filename or stdin to stdout
// filename optional
#include "ucode.c"

int main(int argc, char *argv[])
{
	char c, last;
	int fd;

	// read from stdin:
	if (argc == 1)
	{
		fd = 0;
	}
	// read from file
	else
	{
		fd = open(argv[1], O_RDONLY);
	}

	// Make sure fd got somethin
	if (fd < 0)
	{
		printf("Could not find the file\n");
		return -1;
	}

	// Read!
	while(read(fd, &c, 1) > 0)
	{
		putc(c);

		// Reading from stdin, look for \r
		if (fd == 0)
		{
			if (c == '\r' && (last != '\n' && lc != '\r'))
			{
				putc('\n');
				putc('\r');
			}
		}
		// Reading from file, look for \n
		else
		{
			if (c == '\n' && (last != '\n' && lc != '\r'))
			{
				putc('\r');
			}
		}

		last = c;
	}

	close(fd);
	exit(0);
}