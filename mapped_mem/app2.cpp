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
    int running = 1;
    while(running){
        
        if(share->writeable == 0){
            char buf[1024];
            printf("Please input\n");
            fgets(buf,1024,stdin);
            strncpy(share->str, buf, sizeof(buf));
            share->writeable = 1;
            if(strncmp(buf,"quit",4) == 0){
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
}
