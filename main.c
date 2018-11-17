#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
  srand(time(NULL));
  int randarr[2] = {rand(), rand()};
  printf("In the beginning there was one. Parent pid is %d\n", getpid());
  int f1 = fork();
  
  if (!f1) {
    printf("The child pid is %d\n", getpid());
    int randsleep = (randarr[0] % 16) + 5;
    sleep(randsleep);
    printf("Child %d process woke up after %d seconds\n", getpid(), randsleep);
    return randsleep;
  }
  
  else {
    int f2 = fork();
    if (!f2) {
      printf("The child pid is %d\n", getpid());
      int randsleep = (randarr[1] % 16) + 5;
      sleep(randsleep);
      printf("Child %d process woke up after %d seconds\n", getpid(), randsleep);
      return randsleep;
    }
    else {
      int status;
      int childpid = wait(&status);
      printf("The pid of the completed child process was %d\n", childpid);
      printf("The child was asleep for %d seconds\n", WEXITSTATUS(status));
      return 0;
    }
    return 0;
  }
  
}
