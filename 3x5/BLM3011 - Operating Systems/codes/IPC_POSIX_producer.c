#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include <sys/mman.h>

int main(){

  const int SIZE = 4096; // the size (in bytes) of shared memory
  const char* name = "OS"; // name of the shared memory object
  const char* message_0 = "Hello";
  const char* message_1 = " World!";

  int shm_fd; // shared memory file descriptor
  void *ptr; // pointer to shared memory object

  shm_fd = shm_open(name,O_CREAT|O_RDWR, 0666); //create the shared memory object
  ftruncate(shm_fd, SIZE); // configure the size of the shared memory object
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); // memory map the shared memory object

  sprintf(ptr,"%s",message_0);
  ptr += strlen(message_0);
  sprintf(ptr," %s",message_1);
  ptr += strlen(message_1);

  return 0;
}
