

#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>






int main(void)
{
  sem_t sem1;
  // Error checking omitted for expository purposes
  sem_init(&sem1, 1, 1); 
  pid_t pid;
  pid = fork();
  if(pid < 0){
	printf("pid error ");
	exit(1);	
  }

  if(pid == 0 ){
  sem_wait(&sem1); 
    printf("\nEntered..\n"); 
  
    //critical section 
    sleep(4); 
      
    //signal 
    printf("\nJust Exiting...\n"); 
    sem_post(&sem1); 
}
  else{
	wait(NULL);

}
  
  return 0;
}
