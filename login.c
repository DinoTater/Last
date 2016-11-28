char *tty;
int stdin, stdout, stderr;

int checkPassword(char user[], char passwd[]);
int uid, gid;
char uname[64], home[64], program[64]; 

main(int argc, char *argv[])	// invoked by exec("login /dev/ttyxx")
{
	char user[64], passwd
	tty = argv[1];

	close(0);
	close(1);
	close(2);

	stdin = open(tty, READ);
	stdout = open(tty, WRITE);
	stderr = open(tty, ERROR);

	settty(tty);

	printf("ABLOGIN : open %s as stdin, stdout, stderr\n", tty);

	signal(2,1);  // ignore Control-C interrupts so that 
	                // Control-C KILLs other procs on this tty but not the main sh

	while (1)
	{
		printf("Username: ");
		gets(user);
		printf("Password: ");
		gets(passwd);

		// Need function to check password with /etc/passwd
		if(checkPassword(user, passwd))
		{
			printf("Logging in as %s\n", user);
			chuid(uid, gid);
			chdir(home);
			exec(program);
		}

		else
		{
			printf("Login failed.\n");
		}
	}
}

int checkPassword(char user[], char passwd[])
{
	int file = open("/etc/passwd", READ);
	char *token, buffer[1024];

	if (file == null)
	{
		printf("Cannot find password file\n");
		return 0;
	}

	if (read(file, buffer, 1024) < 0)
	{
		printf("Cannot read password file\n");
		return 0;
	}

	token = strtok(buffer, ":");
	while(token != null)
	{
		if(!strcmp(token, user))
		{
			token = strtok(null, ":");

			if(!strcmp(token, passwd))
			{
				uid = atoi(strtok(null, ":")); // get uid
				gid = atoi(strtok(null, ":")); // get gid
				strcpy(uname, strtok(null, ":")) // get user name
				strcpy(home, strtok(null, ":")) // get user home directory
				strcpy(program, strtok(null, ":")) // get user program

				close(file);
				return 1;
			}
		}

		// If we make it here, not the user we are looking for
		token = strtok(null, ":");
	}

	// Close file, no matter results
	close(file);
	return 0;
}