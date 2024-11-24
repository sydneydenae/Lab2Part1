#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include  <string.h>


#define   MAX_COUNT  200
#define   BUF_SIZE   100


void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
  pid_t  pid1, pid2;

  pid1 = fork();
  if (pid1 == 0) {
      ChildProcess();
  } else {
    pid2 = fork();
      if (pid2 == 0) {
        ChildProcess();
      } else {
        ParentProcess();
      }
  }
  return;
}

void  ChildProcess(void)
{
  srandom(3);

  int randLoop = random() % 30;
  pid_t  pid = getpid();
  pid_t  ppid = getppid();
  int   i;
  char   buf[BUF_SIZE];


  for (i = 1; i <= randLoop; i++){
    int randSleep = random() % 10;
    sprintf(buf, "Child Pid: %d is going to sleep!\n", pid);
    write(1, buf, strlen(buf));
    sleep(randSleep);
    sprintf(buf, "Child Pid: is awake!\nWhere is my Parent: %d ?\n\n", ppid);
    write(1, buf, strlen(buf));
  }
  sprintf(buf, "   *** Child process %d is done ***\n", pid);
  write(1, buf, strlen(buf));
  exit(0);
}

void  ParentProcess(void)
{
  int status;
  char   buf[BUF_SIZE];


  pid_t childPid = wait(&status);
  sprintf(buf, "   *** Child pid %d has completed ***\n", childPid);
  write(1, buf, strlen(buf));

  childPid = wait(&status);
  sprintf(buf, "   *** Child pid %d has completed ***\n", childPid);
  write(1, buf, strlen(buf));

  sprintf(buf, "*** Parent is done ***\n");
  write(1, buf, strlen(buf));
}