#include "ucode.c"
#include "helper.c"
	
// 'more' as in Unix
// filename optional


int main(int argc, char *argv[])
{

	char c, *tty, inBuf[1024];
	int input, ttyin, ttyout, LRead, rows;

	gettty(tty);
	ttyin = open(tty, O_RDONLY);
	ttyout = open(tty, O_WRONLY);

	if (argc == 2) {
		input = open(argv[1], O_RDONLY);
	}

	for(rows = 20; rows > 0; rows--) {
		LRead = readLine(input, inBuf);
		if (!LRead)
			exit(1);
		write(1, inBuf, LRead);
		write(ttyout, "\r", 1);
	}

	while(1) {
		read(ttyin, &c, 1);

		switch (c)
		{
			// Options: Enter/one line, space/pageDown, q/quit 
			
			case '\r':
				rows = 1;
				break;
			case ' ':
				rows = 20;
				break;
			case 'q':
				exit(1);
				break;
			default:
				rows = 1;
				break;
		}
		for(; rows > 0; rows--) {
			LRead = readLine(input, inBuf);
			if(!LRead)
				exit(1);
			write(1, inBuf, LRead);
			write(ttyout, "\r", 1);
		}
	}
}

