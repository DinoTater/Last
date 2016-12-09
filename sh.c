#include "helper.c"
#include "ucode.c"

int do_pipe(char *cmdLine, int *pd);
int do_command(char *cmdLine);
int divide(char *cmdLine, char *head, char *tail);

/*
YOUR sh must support
(1). logout/exit :  terminate
(2). simple command exceution, e.g. ls, cat, ....
(3). I/O redirection:  e.g. cat < infile;  cat > outfile, etc.
(4). (MULTIPLE) PIPEs: e.g. cat file | l2u | grep LINE 


Write YOUR OWN sh.c to support I/O redirections and pipes:

     Examples:  cat [filename]        // NOTE: cat may NOT need a filenmae
                cat [filename] >  newfile 
                cat [filename] >> appendFile                           
                a.out < inFile        // read inputs from inFile 
                cat filename | more
                cat filename | grep test
                cat filename | l2u | grep PRINT

                cat filename > /dev/lp0   // print filename
                cp  filename /dev/lp0     // print filename
*/          

int main(int argc, char *argv[]) {
    char tempLine[128], cmd_line[128], *cmd;
    int status;
    char uname[32], passwd[32];

	while(1) {
        printf("SUPERshell: ");
        bzero(tempLine, 128);
        bzero(cmd_line, 128);
        gets(tempLine);
        strncpy(cmd_line, tempLine, 128);
        cmd = strtok(tempLine, " ");
        
        if (!strcmp(cmd, "cd") || !strcmp(cmd, "logout") || !strcmp(cmd, "su")) {
            if (!strcmp(cmd, "cd")){
                cmd = strtok(0, ' ');
                chdir(cmd);
            }
            else if (!strcmp(cmd, "logout")) {
                exit(1);
            }
            else {
                printf("Enter username: ");
                gets(uname);
                printf("Enter password: ");
                gets(passwd);
                if(!strcmp(uname, "root") && !strcmp(passwd, "12345"))
                {
                    chuid(0,0);
                    chdir("/");
                    printf("Welcome %s.\n", name);
                }
                else {
                    printf("Username/Password incorrect. You are not authorized in this area.\n");
                }
            }
            continue;
        }
        else {
            pid = 0;
            pid = fork();
            if (pid) {
                if (!strstr(cmd_line, "&"))
                    pid = wait(&status);
                else
                    continue;
            }
            else
                do_pipe(cmd_line, 0);
        }
    }
}

int do_pipe(char *cmdLine, int *pd) {
    int scan, hasPipe = 0, lpd[2];
    char *head, *tail;

    if (pd) { // if has a pipe passed in, as WRITER on pipe pd:
        close(pd[0]);
        dup2(pd[1], 1);
        close(pd[1]);
    }
    // divide cmdLine into head, tail by rightmost pipe symbol
    hasPipe = divide(cmdLine, &head, &tail);
    if (hasPipe) {
        // create a pipe lpd;
        pipe(lpd);
        pid = 0;
        pid = fork();
        if (pid) { // parent
            //as READER on lpd:
            close(lpd[1]); dup2(lpd[0], 0); close(lpd[0]);
            do_command(tail);
        }
        else {
            do_pipe(head, lpd);
        }
    }
    else {
        do_command(cmdLine);
    }
}

int do_command(char *cmdLine) {
    /*
    scan cmdLine for I/O redirection symbols;
    do I/O redirections;
    head = cmdLine BEFORE redirections
    exec(head)
    */
    int i = 0, out, in;
    char *file, *cmd;


    while(cmdLine[i]) {
        if (cmdLine[i] == '>' || cmdLine[i] == '<') {
            if (cmdLine[i] == '>') {
                cmdLine[i++] = '\0';
                
                // check for '>>'
                if (cmdLine[i] == '>') {
                    i++;
                    while(cmdLine[i] == ' ')
                        i++;
                    file = cmdLine + i;
                    while(cmdLine[i] != ' ' && cmdLine[i])
                        i++;
                    cmdLine[i] = '\0';
                    i++;
                    close(1);
                    out = open(file, O_WRONLY | O_CREAT | O_APPEND);
                }
                else {
                    while(cmdLine[i] == ' ')
                        i++; // space follows '>'
                    file = cmdLine + i;
                    while(cmdLine[i] != ' ' && cmdLine[i])
                        i++;
                    cmdLine[i] = '\0';
                    i++;
                    close(1);
                    out = open(file, O_WRONLY | O_CREAT | O_TRUNC);
                }
            }
            else if (cmdLine[i] == '<') {
                cmdLine[i++] = '\0';
                
                while(cmdLine[i] == ' ')
                    i++;
                file = cmdLine + i;
                while(cmdLine[i] != ' ' && cmdLine[i])
                    i++;
                cmdLine[i] = '\0';
                i++;
                close(0);
                in = open(file, O_RDONLY);
            }
        }
        i++;
    }
    exec(cmdLine);
}

int divide(char *cmdLine, char **head, char **tail) {
    /*
    divide cmdLine into head and tail by rightmost | symbol
    cmdLine = cmd1 | cmd2 | ... | cmdn-1 | cmdn
              |<----------head---------->| tail |; return 1;
    cmdLine = cmd1 ==> head=cmd1, tail = null;     return 0;
    */
    int i;
    
    for (i = 128; i > 0; i--) {
        if (cmdLine[i] == '|') {
            *tail = cmdLine + i + 1;
            printf("tail: %s\n", *tail);
            *head = cmdLine;
            cmdLine[i] = '\0';
            printf("head: %s\n", *head);
            return 1;
        }
    }
    *head = cmdLine;
    *tail = 0;
    return 0;
}

