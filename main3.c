#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#define   MAX_COUNT  200

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

  for (i = 1; i <= randLoop; i++){
    int randSleep = random() % 10;
    printf("Child Pid: %d is going to sleep!\n", pid);
    sleep(randSleep);
    printf("Child Pid: is awake!\nWhere is my Parent: %d ?\n\n", ppid);
  }
  printf("   *** Child process %d is done ***\n", pid);
  exit(0);
}

void  ParentProcess(void)
{
  int status;

  pid_t childPid = wait(&status);
  printf("   *** Child pid %d has completed ***\n", childPid);

 childPid = wait(&status);
  printf("   *** Child pid %d has completed ***\n", childPid);

  printf("*** Parent is done ***\n");
}