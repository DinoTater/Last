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


int main(int argc, char *argv[])
{
	
}

int find_cmd(char *name)
{
    // return command index
    int i;

    for (i = 0; cmd[i]; i++)
    {
        if (!strcmp(cmd[i], name))
            return i;
    }
    
    return -1;
}
