char *tty;

main(int argc, char *argv[])	// invoked by exec("login /dev/ttyxx")
{
	tty = argv[1];

	 1. close(0); close(1); close(2); // login process may run on different terms

	 2. // open its own tty as stdin, stdout, stderr

	 3. settty(tty);   // store tty string in PROC.tty[] for putc()

	  // NOW we can use printf, which calls putc() to our tty
	  printf("KCLOGIN : open %s as stdin, stdout, stderr\n", tty);

	  signal(2,1);  // ignore Control-C interrupts so that 
	                // Control-C KILLs other procs on this tty but not the main sh

	  while(1){
	    1. show login:           to stdout
	    2. read user nmae        from stdin
	    3. show passwd:
	    4. read user passwd

	    5. verify user name and passwd from /etc/passwd file

	    6. if (user account valid){
	          setuid to user uid.
	          chdir to user HOME directory.
	          exec to the program in users account
	       }
	       printf("login failed, try again\n");
	  }
}