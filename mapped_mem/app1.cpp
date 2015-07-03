#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <sys/shm.h>  
#include <string.h>
#include "datastruct.h"


int main(){
    key_t shm_key = 1234;
    int shm_id = shmget(shm_key,sizeof(struct data), 0666|IPC_CREAT);
    if( shm_id == -1){
        printf("Error\n");
        return 0;
    }
    void* shm = shmat(shm_id, NULL, 0);
    struct data* share = (struct data*)shm;

    share->writeable = 0;
    int running = 1;
    printf("start\n");
    while(running){
        
        if(share->writeable == 1){
            printf("You are writing: %s\n", share->str);
            share->writeable = 0;
            if(strncmp(share->str,"quit",4) == 0){
                running = 0;
            }
        }else{
            sleep(1);
        }

    }
        if(shmdt(shm) == -1)  
        {  
            printf("shmdt failed\n");  
            return 0;
        }    
        
        if(shmctl(shm_id, IPC_RMID, 0) == -1)  
        {  
            printf("shmctl(IPC_RMID) failed\n");  
            return 0;
        }   
}
