#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void do_what_a_child_will_do(char* a){
  fprintf(stdout,"%s[%d]: Hi mother!\n",a,(int)getpid());
  exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){

  pid_t pid= fork();
  if(pid < 0){
    perror("Fork");
    exit(EXIT_FAILURE);
  }
  if(pid==0){
    do_what_a_child_will_do(argv[0]);
  }
  else{
    wait(NULL);
    fprintf(stdout,"%s[%d]: Hello son!\n", argv[0], (int)getpid());
  }
}
