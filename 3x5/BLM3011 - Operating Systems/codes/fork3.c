#include <unistd.h>
#include <stdio.h>

int main(){
  int seq = 0;
  pid_t pid = fork();

  if(pid == 0){
    printf("[Seq: %d][pid: %d] Child!\n",++seq,(int)getpid());
  }
  else{
    //wait(NULL);
    printf("[Seq: %d][pid: %d] Parent!\n",++seq,(int)getpid());
  }
  printf("[Seq: %d][pid: %d] Both!\n",++seq,(int)getpid());
  return 0;
}
