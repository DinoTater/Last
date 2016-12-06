#include "ucode.c"
#include "helper.h"

char *tty;
char uname[32], pass[32];


int main(int argc, char *argv[]) {
	char temp[32];
	tty = argv[1];

	close(0);
	close(1);
	close(2);

	open(tty, O_RDONLY);
	open(tty, O_WRONLY);
	open(tty, O_WRONLY);

	settty(tty);

	signal(2, 1); //Ignore cntrl+c

	while(1) {
		printf("username: ");
		gets(uname);
		printf("password: ");
		gets(pass);

		checkPass();
	}
}

int checkPass() {
	int file = open("/etc/passwd", O_RDONLY);
	char line[64];
	char temp[64];
	char *comp;
	int i = 0;

	do {
		memset(line,0,strlen(line));
		getLine(file, line, 64);
		printf("line = %s\n", line);
		cpystr(temp, line);
		comp = strtok(line, ":");

		if(strcmp(uname, comp) == 0) {
			// user name is correct
			comp = strtok(0, ":");
			if(strcmp(pass, comp) == 0) {
				printf("Credentials are accredited!\n");
				runUser(temp);
				close(file);				
			}
			else {
				printf("Username/password incorrect.\n");
				exit(1);
			}
		}
		
	} while(line[0] != 0);
	printf("Username/password incorrect\n");
	close(file);
	exit(1);
}

int runUser(char *line) {
	char *name, *home, *program, *next;
	int gid, uid;

	strtok(line, ":");
	strtok(0, ":");
	gid = atoi(strtok(0, ":"));
	uid = atoi(strtok(0, ":"));
	name = strtok(0, ":");
	home = strtok(0, ":");
	program = strtok(0, ":");

	if (next = strchr(program, '\n')) {
		*next = 0;
	}

	chuid(uid, gid);
	chdir(home);

	printf("Welcome %s.\n", name);

	exec(program);
}