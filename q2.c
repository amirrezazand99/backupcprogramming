



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

	int *results;
	results = malloc(sizeof(int) * SR );
	int p_st = pipe(pip); 
	if(p_st < 0 ){
		exit(1);
	}

	for(int i = 0 ; i < 8 ; i++){
		pid = fork();
		if (pid < 0 ){
			printf("fork failed \n");
			exit(1);
		}
		//child
		else if (pid == 0){
			int buffer;
			read(pip[0] , &buffer , INT_SIZE);
			printf("child : %d is %d \n", pid , buffer);

			exit(0);
		}
	}
	//parents
	if(pid > 0 ){

		for(int i = 10000000000 ; i < 2000000000 ; i++){
			write(pip[1] , &i , INT_SIZE);
		}



	}


	return 0;
}