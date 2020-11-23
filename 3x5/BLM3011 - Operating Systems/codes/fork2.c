#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int common_ground = 0;

int main(int argc, char** argv){

  pid_t pid = fork();
  if(pid<0){
    perror("Fork");
    exit(EXIT_FAILURE);
  }
  if(pid == 0){
    common_ground++;
    fprintf(stderr,"slave[%d]: common_ground: %d\n",(int)getpid(),common_ground);
    if(execvp(argv[1],argv+1)){
      fprintf(stderr,"slave[%d]: no can do!: %s\n", (int)getpid(), strerror(errno));

    }
    exit(EXIT_FAILURE);
  }
  wait(NULL);
  fprintf(stdout,"master[%d]: common ground: %d\n",(int)getpid(),common_ground);
  fprintf(stdout,"master[%d]: i did nothing!\n",(int)getpid());
  return 0;
}
