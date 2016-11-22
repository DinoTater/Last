int pid, child, status;
int stdin, stdout;

#include "ucode.c"

main(int argc, char *argv[])
{
  1. // open /dev/tty0 as 0 (READ) and 1 (WRTIE) in order to display messages

  2. // Now we can use printf, which calls putc(), which writes to stdout
     printf("KCINIT : fork a login task on console\n"); 
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
			fork another login child
		else
			print("INIT : buried an orphan child %d\n", pid);
	}
}