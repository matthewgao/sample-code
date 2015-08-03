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
class test{
    public:
    test(){}
    ~test(){}

    static int i;
};

int test::i = 0;

int
main(){
    
    if(fork() == 0){
        str[0] = 'd';
        test::i = 2; 
        printf("Child %s\n",str);
        printf("Child addr %lx\n",(unsigned long)str);
        printf("Child test static %lx, %d\n",(unsigned long)test::i,test::i);
    }else{
        sleep(5);
        //test::i = 2: 
        printf("Parant %s\n",str);
        printf("Parant addr %lx\n",(unsigned long)str);
        printf("Parent test static %lx, %d\n",(unsigned long)test::i,test::i);
    }
    return 0;
}
