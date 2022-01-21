/*
  This example program illustrates the use of mutex variables in a
  Pthreads program. The main data is made available to all threads through 
  a globally accessible structure. Each thread works on a different 
  part of the data. The main thread waits for all the threads to complete 
  their computations, and then it prints the resulting sum.
  Compile with 'gcc -O3 -pthread dotprod_mutex.c -o dotprod_mutex'
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
  The following structure contains the necessary information  
  to allow the function "dotprod" to access its input data and 
  place its output into the structure.
*/
typedef struct {
  double      *a;  // a and b are the vectors for which we 
  double      *b;  // compute the dot product 
  double     sum;  // the result of the dotproduct 
  int     veclen;  // length of vectors a and b 
} dotdata;

#define NTHREADS 8
#define VECLEN 10000

// Define globally accessible variables and a mutex 
dotdata dotstr;                 // Structure with data 
pthread_t thread_id[NTHREADS];  // Thread ids
pthread_mutex_t mutexsum;       // Mutex protecting the sum value

/*
  The function dotprod is activated when the thread is created.
  All input to this routine is obtained from a structure 
  of type dotdata and all output from this function is written into
  the same structure. When a thread is created we pass a single
  argument to the activated function - a thread number. 
  All  the other information required by the function is accessed from
  the globally accessible structure. 
*/
void *dotprod(void *arg) {
  // Define local variables
  int i, start, end, len ;
  long int offset;
  double mysum, *x, *y;

  offset = (long int)arg;   // Thread number 
  len = dotstr.veclen;      // Vector length 
  start = offset*len;       // Start of this threads slice of the vectors
  end   = start + len;      // End of the slice
  x = dotstr.a;             // Pointers to the vectors a and b
  y = dotstr.b;

  // Compute the dot product in the local variable mysum
  mysum = 0.0;
  for (i=start; i<end ; i++) {
    mysum += (x[i] * y[i]);
  }
  // Lock a mutex before updating the value in the shared
  // structure, and unlock it when ready
  pthread_mutex_lock (&mutexsum);     // Lock the mutex 
  //mysum += dotstr.sum;
  //sleep(1);
  //dotstr.sum = mysum;                
  dotstr.sum += mysum;                // Update the shared variable
  pthread_mutex_unlock (&mutexsum);   // Unlock the mutex 
  
  pthread_exit(NULL);
}

/* 
   The main program creates threads which do all the work and then 
   print out the result when ready. Before creating the threads,
   the input data is created. Since all threads update a shared structure, we
   need a mutex for mutual exclusion. The main thread needs to wait for
   all threads to complete. All threads are created as joinable. 
   Note also that we free handles when they are no longer needed.
*/

int main (int argc, char *argv[]) {
  long int i;
  double *a, *b;
  void *status;
  pthread_attr_t attr;   // Attribute object for the threads
  
  // Allocate the vectors a and b
  a = (double*) malloc (NTHREADS*VECLEN*sizeof(double));
  b = (double*) malloc (NTHREADS*VECLEN*sizeof(double));
  
  // Initialize a and b to some values
  for (i=0; i<VECLEN*NTHREADS; i++) {
    a[i]=1.0;
    b[i]=a[i];
  }
  
  // Set up data in the structure dotstr
  dotstr.veclen = VECLEN; 
  dotstr.a = a; 
  dotstr.b = b; 
  dotstr.sum=0.0;
  
  // Initialize the mutex
  pthread_mutex_init(&mutexsum, NULL);

  // Initialize the attribute for the threads
  // so they are created as joinable
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // Create threads to perform the dotproduct
  for(i=0;i<NTHREADS;i++) {
    // Each thread works on a different set of data specified by 'i'
    pthread_create(&thread_id[i], &attr, dotprod, (void *)i); 
  }
  
  // Destroy the attribute object
  pthread_attr_destroy(&attr);

  // Wait on the other threads
  for(i=0;i<NTHREADS;i++) {
    pthread_join(thread_id[i], &status);
  }

  // After joining, print out the results and cleanup
  printf ("Sum =  %6.2f \n", dotstr.sum);
  free (a);
  free (b);
  pthread_mutex_destroy(&mutexsum);
  pthread_exit(NULL);
}  


