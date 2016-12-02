int pid, child, status;
int stdin, stdout;

#include "ucode.c"

main(int argc, char *argv[])
{
  	 // open /dev/tty0 as 0 (READ) and 1 (WRITE) in order to display messages
  	 stdin = open("/dev/tty0", 0);
  	 stdout = open("/dev/tty1", 1);

  	 // Now we can use printf, which calls putc(), which writes to stdout
     printf("ABINIT : fork a login task on console\n"); 
     child = fork();

     if (child)
         parent();
     else             // login task
         login();
}

int login()
{
	exec("login /dev/tty0");
}

int parent()
{
	while(1)
	{
		printf("DinoINIT : waiting .....\n");

		pid = wait(&status);

		if (pid == child)
		{
			// fork another login child
			child = fork();
			if (!child)
				login();
		}
		else
			printf("INIT : buried an orphan child %d\n", pid);
	}
}