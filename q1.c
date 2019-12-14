



#include <stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>


#define SR 10000000

#define INT_SIZE sizeof(int)

int check_prime(int n){
	for(int i =2 ; i < n ; i++)
		if (n % i == 0 ){
			return 0;

		}
	return 1 ;

}

int main(){


	int pid ;
	int pip[2];
	sem_t proc_sem;
	int *results;

	int * counter = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
	int childstate;

	results = (int*)malloc(sizeof(int) * SR );
	int p_st = pipe(pip); 
	if(p_st < 0 ){
		exit(1);
	}


	//initializing proc_semaphore
	sem_init(&proc_sem, 1, 1); 

	for(int i = 0 ; i < 8 ; i++){
		pid = fork();
		if (pid < 0 ){
			printf("fork failed \n");
			exit(1);
		}
		//child
		else if (pid == 0){
			// results[0] = 0;
			*counter = 0;
			int buffer;
			int checker;
			while(*counter < 10000000){
				
				read(pip[0] , &buffer , INT_SIZE);
				checker = check_prime(buffer);
				if(checker == 1 ){
					sem_wait(&proc_sem);
					results[*counter] = buffer;
					*counter  = *counter + 1 ;
					printf("child : %d is %d \n", i , *counter - 1) ;//buffer);//*counter);
					sem_post(&proc_sem);
				}
			
			}

			// counter=0;
			// while(counter < 1000000 ){
			// 	read(pip[0] , &buffer , INT_SIZE);
			// 	printf("child : %d is %d \n", i , buffer);
			// 	counter++;
			// 	}

			exit(0);
		}
	}
	//parents
	if(pid > 0 ){
		
		for(int i = 10000000000 ; i < 2000000000 ; i++){

			// waitpid (pid, &childstate, 0); 
			if( *counter < 10000000){
				write(pip[1] , &i , INT_SIZE);
			}
			else{
				exit(0);
			}
		}



	}


	return 0;
}
