#include  <stdio.h>
#include  <sys/types.h>
#include  <string.h>


#define   MAX_COUNT  200
#define   BUF_SIZE   100

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
     pid_t  pid;
     pid = fork();
     if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void  ChildProcess(void){
     int   i;
     char   buf[BUF_SIZE];

     for (i = 1; i <= MAX_COUNT; i++){
          sprintf(buf, "This line is from child, value = %d\n", i);
          write(1, buf, strlen(buf));
     }
     sprintf(buf, "   *** Child process is done ***\n");
     write(1, buf, strlen(buf));
}

void  ParentProcess(void)
{
     int   i;
     char   buf[BUF_SIZE];
     for (i = 1; i <= MAX_COUNT; i++){
          sprintf(buf, "This line is from child, value = %d\n", i);
          write(1, buf, strlen(buf));
     }
     sprintf(buf, "*** Parent is done ***\n");
     write(1, buf, strlen(buf));
}