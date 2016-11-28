// cp    src dest           // src may be a file or DIR
#include "ucode.c"

int main(int argc, char *argv[])
{
	char buffer[1024];
	int src, dest, i;

	if(argc < 3)
	{
		printf("Use: cp src dest");
		return 1;
	}

	// open src and dest
	src = open(argv[1], O_RDONLY);
	dest = open(argv[2], O_WRONLY | O_CREAT);

	// read from src, write dest
	while((i = read(src, buffer, 1024)) > 0)
		write(dest, buffer, i);

	close(src);
	close(dest);
	return 0;
}