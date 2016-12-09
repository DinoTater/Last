#define TTY0 0
#define TTYS0 1
#define TTYS1 2

int pid, dev1, dev2, dev3, status;
int stdin, stdout;

#include "ucode.c"  //<========== AS POSTED on class website

main(int argc, char *argv[])
{
  //1. // open /dev/tty0 as 0 (READ) and 1 (WRTIE) in order to display messages
      stdin = open("/dev/tty0", O_RDONLY);
      stdout = open("/dev/tty0", O_WRONLY);
  //2. // Now we can use printf, which calls putc(), which writes to stdout
     printf("SUPERinit : fork login tty0\n"); 
     dev1 = fork();

     if (dev1) //parent
     {
        printf("SUPERinit : fork login ttyS0\n");  
        dev2 = fork();
        if(dev2) //parent
        {
          printf("SUPERinit : fork login ttyS1\n"); 
          dev3 = fork();
          if(dev3) //parent
          {
            printf("parent\n");
            parent();
          }
          else //Proc 4
          {
            printf("else\n");
            login(TTYS1);
          }
        }
        else //Proc 3
        {
          printf("3\n");
          login(TTYS0);
        }
     }
     else //Proc 2       
     {
       printf("4\n");
       login(TTY0);
     }
}

int login(int dev)
{
  switch(dev)
  {
    case TTY0:
      exec("login /dev/tty0");
      break;
    case TTYS0:
      exec("login /dev/ttyS0");
      break;
    case TTYS1:
      exec("login /dev/ttyS1");
      break;
  }
}
      
int parent()
{
  while(1){
    printf("SUPERinit : wait for ZOMBIE child...\n");

    pid = wait(&status);
    printf("Left wait\n\n");
    if (pid == dev1)
    {
      printf("Dev1\n");
      dev1 = fork();
      if(dev1)
      {
        //wait for children to die
      }
      else
      {
        login(TTY0);
      }
    }
    else if (pid == dev2)
    {
      printf("Dev2\n");
      dev2 = 0;
      dev2 = fork();
      if(dev2)
      {
        //wait for children to die
      }
      else
      {
        login(TTYS0);
      }
    }
    else if (pid == dev3)
    {
      printf("Dev3\n");
      dev3 = 0;
      dev3 = fork();
      if(dev3)
      {
        //wait for children to die
      }
      else
      {
        login(TTYS1);
      }
    }        
    else 
        printf("SUPERinit : buried an orphan child %d\n", pid);
  }
}