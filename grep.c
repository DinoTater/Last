// grep  pattern [filename] // print lines containing pattern
// filename optional


int main(int argc, char *argv[])
{
	// Check for correct usage
	if (argc == 1)
	{
		printf("Usage: grep patter [file]");
		exit(1);
	}
	else if (argc == 2)
	{
		fd = 0;
	}
	else
	{
		fd = open(argv[2], O_RDONLY);
	}

	if (fd >= 0)
	{
		// Find that pattern!!
	}
}