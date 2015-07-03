#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>


/*
 * Child process will reuse the variable which is in parant 
 * process, but COPY ON WRITE, Child and Parent will have the 
 * same virtual address, but virtual addr point to different 
 * phycial address 
 */
static char str[10]="abc";

int
main(){
    
    if(fork() == 0){
        str[0] = 'd';
        printf("Child %s\n",str);
        printf("Child addr %lx\n",(unsigned long)str);
    }else{
        sleep(5);
        printf("Parant %s\n",str);
        printf("Parant addr %lx\n",(unsigned long)str);
    }
    return 0;
}
