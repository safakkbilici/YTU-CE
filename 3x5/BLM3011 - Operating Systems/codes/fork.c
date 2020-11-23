#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){

  pid_t pid;
  pid = fork();

  if(pid<0){ // error occured
    fprintf(stderr,"Fork failed");
    return -1;
  }
  else if(pid==0){ //child process
    execlp("/bin/ls","ls",NULL);
  }
  else{ // parent process
    wait(NULL); // parent will wait for the child to complete
    printf("Child Complete");
  }
  return 0;
}
