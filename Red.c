#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int patron_vertical(int matriz[7][7]){

    int   _shm_id[49];
    key_t _shm_key;
     
    struct shmid_ds shmidds[49];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
     
    int status;

    for(int i = 0; i < 49; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
                for(int k = 0; k < 7; k++)
                {
                    if(matriz[i][j]==1)
                        if(matriz[i][j+1]==1)
                            if(matriz[i][j+2]==1)
                                if(matriz[i][j+3]==1)
                                    return 1;            

                    exit(EXIT_SUCCESS);
                }   
            else if(pid > 0)
            {
                for(int k = 0; k < 49; k++)
                {
                    shmctl(_shm_id[k], IPC_STAT, &shmidds[k]); 
                }
                 
                pid_counter++;
            }
            else
            {
                //perror(program_invocation_name);
                exit(EXIT_FAILURE);
            }
        }
        
    }

    for(int i = 0; i < 49; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);
     
    for(int i = 0; i < 49; i++)
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);

    return 0;
}

int patron_horizontal(int matriz[7][7]){
    int   _shm_id[49];
    key_t _shm_key;
     
    struct shmid_ds shmidds[49];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
     
    int status;

    for(int i = 0; i < 49; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
                for(int k = 0; k < 7; k++)
                {
                    if(matriz[i][j]==1)
                        if(matriz[i+1][j]==1)
                            if(matriz[i+2][j]==1)
                                if(matriz[i+3][j]==1)
                                    return 1;

                    exit(EXIT_SUCCESS);
                }   
            else if(pid > 0)
            {
                for(int k = 0; k < 49; k++)
                {
                    shmctl(_shm_id[k], IPC_STAT, &shmidds[k]); 
                }
                 
                pid_counter++;
            }
            else
            {
                //perror(program_invocation_name);
                exit(EXIT_FAILURE);
            }
        }
        
    }

    for(int i = 0; i < 49; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);

    for(int i = 0; i < 49; i++)
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);

    return 0;
}


int patron_diagonal1(int matriz[7][7]){

    int   _shm_id[49];
    key_t _shm_key;
     
    struct shmid_ds shmidds[49];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
     
    int status;

    for(int i = 0; i < 49; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
                for(int k = 0; k < 7; k++)
                {
                    if(matriz[i][j]==1)
                        if(matriz[i+1][j+1]==1)
                            if(matriz[i+2][j+2]==1)
                                if(matriz[i+3][j+3]==1)
                                    return 1;

                    exit(EXIT_SUCCESS);
                }   
            else if(pid > 0)
            {
                for(int k = 0; k < 49; k++)
                {
                    shmctl(_shm_id[k], IPC_STAT, &shmidds[k]); 
                }
                 
                pid_counter++;
            }
            else
            {
                //perror(program_invocation_name);
                exit(EXIT_FAILURE);
            }
        }
        
    }
     
    for(int i = 0; i < 49; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);

    for(int i = 0; i < 49; i++)
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);
    return 0;
}

int patron_diagonal2(int matriz[7][7]){

    int   _shm_id[49];
    key_t _shm_key;
     
    struct shmid_ds shmidds[49];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
     
    int status;

    for(int i = 0; i < 49; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
                for(int k = 0; k < 7; k++)
                {
                    if(matriz[i][j]==1)
                        if(matriz[i-1][j-1]==1)
                            if(matriz[i-2][j-2]==1)
                                if(matriz[i-3][j-3]==1)
                                    return 1;

                    exit(EXIT_SUCCESS);
                }   
            else if(pid > 0)
            {
                for(int k = 0; k < 49; k++)
                {
                    shmctl(_shm_id[k], IPC_STAT, &shmidds[k]); 
                }
                 
                pid_counter++;
            }
            else
            {
                //perror(program_invocation_name);
                exit(EXIT_FAILURE);
            }
        }
        
    }

    for(int i = 0; i < 49; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);

    for(int i = 0; i < 49; i++)
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);
    return 0;
}


void revisar(int matriz[7][7], int vect[4]){
    
    int res;
    for(int i=0;i<4;i++){

        if(i==0){
            res = patron_vertical(matriz);
            vect[i]=res;
        }

        if(i==1){
            res = patron_horizontal(matriz);
            vect[i]=res;
        }

        if(i==2){
            res = patron_diagonal1(matriz);
            vect[i]=res;
        }

        if(i==3){
            res = patron_diagonal2(matriz);
            vect[i]=res;
        }    
    }
}

int main(int argc, char **argv)
{
    //Letra E
    int matriz_1[7][7]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0};
    int matriz_2[7][7]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int matriz_3[7][7]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int matriz_4[7][7]={0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0};
    int matriz_5[7][7]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int matriz_6[7][7]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int matriz_7[7][7]={0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int matriz_8[7][7]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int matriz_9[7][7]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int vect[4],final_E[36];  


    revisar(matriz_1,vect);
    memcpy(final_E, vect, sizeof(int) * 4);

    revisar(matriz_2,vect);
    memcpy(final_E + 4, vect, sizeof(int) * 4);

    revisar(matriz_3,vect);
    memcpy(final_E + 8, vect, sizeof(int) * 4);

    revisar(matriz_4,vect);
    memcpy(final_E + 12, vect, sizeof(int) * 4);

    revisar(matriz_5,vect);
    memcpy(final_E + 16, vect, sizeof(int) * 4);

    revisar(matriz_6,vect);
    memcpy(final_E + 20, vect, sizeof(int) * 4);

    revisar(matriz_7,vect);
    memcpy(final_E + 24, vect, sizeof(int) * 4);

    revisar(matriz_8,vect);
    memcpy(final_E + 28, vect, sizeof(int) * 4);

    revisar(matriz_9,vect);
    memcpy(final_E + 32, vect, sizeof(int) * 4);

    for (int i = 0; i < 36; i++)
      printf("Dato %i: %d\n",i+1,final_E[i]);

return 0;
}
