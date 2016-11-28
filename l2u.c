//l2u   [f1 f2]            // convert lower case to upper case
#include "ucode.c"

int checkLower(char c)
{
	int i;
	char *lowers = "abcdefghijklmnopqrstuvwxyz";

	for (i = 0; i < 26; i++)
	{
		if (c == lowers[i])
			return 1;
	}

	// We missed, must be upper
	return 0;
}

int main(int argc, char *argv[])
{
	char buffer[1024], outbuf[1024];
	int fd1, fd2, i, input;

	// No files input
	if (argc == 1)
	{
		fd1 = 0;
		fd2 = 1;
	}
	// One file input, read that, write to terminal
	else if (argc == 2)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = 1;
	}
	// Both files given, read to first, write to second
	else if (argc == 3)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_WRONLY | O_CREAT);
	}

	// Make sure fd's workin
	if (fd < 0 || fd2 < 0)
	{
		printf("Error reading files\n");
		return 0;
	}

	do
	{
		input = read(fd1, buffer, 1024);

		for (i = 0; i < input; i++)
		{
			if(checkLower(buffer[i]) == 1)
				outbuf[i] = (buffer[i] - 32);
			else
				outbuf[i] = buffer[i];
		}

		if (fd2 != 1)
			write(fd2, outbuf, input);
		else
		{
			for(i = 0; i < input; i++)
			{
				if(outbuf[i] == '\n')
					printf('\n');
				else
					printf("%c", outbuf[i]);
			}
		}
	} while (input == 1024);

	close(fd1);
	close(fd2);
	return 0;
}