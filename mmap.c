


#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(void) {
    int * shared = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    pid_t child;
    int childstate;
    //printf("%d\n", *shared);
    if((child=fork())==0){
            *shared = 1;
            printf("%d\n", *shared);
            *shared = *shared + 1;
            exit(0);
    }
    waitpid (child, &childstate, 0); 
    printf("%d\n",*shared);
}
