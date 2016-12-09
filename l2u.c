#include "helper.c"
#include "ucode.c"

//l2u   [f1 f2]            // convert lower case to upper case

int checkLower(char c);

int main(int argc, char *argv[])
{
	char buffer[1024], *tty, c;
	int i, j, n, input, output, ttyout;

	gettty(tty);
	input = 0;
	ttyout = open(tty, O_WRONLY);

	if (argc == 2)
	{
		input = open(argv[1], O_RDONLY);
		while(n = read(input, buffer, 1024)) {
			for (i = 0; i < n; i++)
			{
				if(checkLower(buffer[i]) == 1)
					buffer[i] = (buffer[i] - 32);
				write(ttyout, buffer + i, 1);
				if(buffer[i] == '\n')
					write(ttyout, "\r", 1);
			}
		}
		close(input);
	}

	else if (argc == 3)
	{
		input = open(argv[1], O_RDONLY);
		output = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
		while(n = read(input, buffer, 1024)) {
			for (i = 0; i < n; i++)
			{
				if(checkLower(buffer[i]) == 1)
					buffer[i] = (buffer[i] - 32);
				write(output, buffer + i, 1);
			}
		}
		close(input);
		close(output);
	}

	else {
		while(read(0, &c, 1)) {

			if(c <= 'z' && c >= 'a') {
				c = c - 32;
			}
			if(c == '\n') {
				write(ttyout, "\r", 1);
				buffer[i] = c;
				write(1, &c, 1);
				bzero(buffer, 1024);
				i = 0;
			}
			else if(c == '\r') {
				write(ttyout, "\r", 1);
				buffer[i] = '\n';
				c = '\n';
				write(1, &c, 1);
				write(ttyout, buffer, strlen(buffer));
				write(ttyout, "\r", 1);
				bzero(buffer, 1024);
				i = 0;
			}
			else {
				buffer[i] = c;
				write(1, &c, 1);
				i++;
			}
		}
	}

	close(ttyout);
	
	exit(1);
}

int checkLower(char c)
{
	int i;
	//char *lowers = "abcdefghijklmnopqrstuvwxyz";

	if (c <= 'z' && c >= 'a')
		return 1;

	// We missed, must be upper
	return 0;
}
