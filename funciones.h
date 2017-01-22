#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void Multi(int vec[4], int matriz[4][4]){
    
     
    int   _shm_id[16];
    key_t _shm_key;
     
    struct shmid_ds shmidds[16];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
    int *matrix_element;
     
    int status;

    printf("\nEl vector de entrada es: [");
    for (int i = 0; i < 4; ++i)
    {
        printf("%d,",vec[i] );
    }
    printf("]\n");

    for(int i = 0; i < 16; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
            {
                matrix_element = (int *) shmat(shm_id, NULL, 0);
                 
                *matrix_element= 0;
                 
                for(int k = 0; k < 4; k++)
                {
                    *matrix_element+= vec[i] * vec[j];
                     
                    shmdt(matrix_element);
                 
                    exit(EXIT_SUCCESS);
                }
            }   
            else if(pid > 0)
            {
                for(int k = 0; k < 16; k++)
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
     
    //sleep(3);
     
    for(int i = 0; i < 16; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);
     
    //sleep(3);
     
    for(int i = 0, j = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
        {
            matrix_element = (int *) shmat(_shm_id[j], NULL, 0);
            matriz[i][k]= *matrix_element;
            shmdt(matrix_element);
            j++;
        }
     
    for(int i = 0; i < 16; i++)
    {
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);
    }

    return;
}

void Rest(int matriz[4][4], int I[4][4]){
    
     
    int   _shm_id[16];
    key_t _shm_key;
     
    struct shmid_ds shmidds[16];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
    int *matrix_element;
     
    int status;
    
    for(int i = 0; i < 16; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
            {
                matrix_element = (int *) shmat(shm_id, NULL, 0);
                 
                *matrix_element= 0;
                 
                for(int k = 0; k < 4; k++)
                {
                    *matrix_element+= matriz[i][j] -I[i][j];
                     
                    shmdt(matrix_element);
                 
                    exit(EXIT_SUCCESS);
                }
            }   
            else if(pid > 0)
            {
                for(int k = 0; k < 16; k++)
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
     
    //sleep(3);
     
    for(int i = 0; i < 16; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);
     
    //sleep(3);
     
        for(int i = 0, j = 0; i < 4; i++)
            for(int k = 0; k < 4; k++)
            {
                matrix_element = (int *) shmat(_shm_id[j], NULL, 0);
                matriz[i][k]= *matrix_element;
                shmdt(matrix_element);
                j++;
            }  
     
        for(int i = 0; i < 16; i++)
        {
            shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);
        }
    return;
}
 
void Sum(int matriz_1[4][4], int matriz_2[4][4]){
    
     
    int   _shm_id[16];
    key_t _shm_key;
     
    struct shmid_ds shmidds[16];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
    int *matrix_element;
     
    int status;
    
    for(int i = 0; i < 16; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
            {
                matrix_element = (int *) shmat(shm_id, NULL, 0);
                 
                *matrix_element= 0;
                 
                for(int k = 0; k < 4; k++)
                {
                    *matrix_element+= matriz_1[i][j]+matriz_2[i][j];
                     
                    shmdt(matrix_element);
                 
                    exit(EXIT_SUCCESS);
                }
            }   
            else if(pid > 0)
            {
                for(int k = 0; k < 16; k++)
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
     
    //sleep(3);
     
    for(int i = 0; i < 16; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);
     
    //sleep(3);
     
    for(int i = 0, j = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
        {
            matrix_element = (int *) shmat(_shm_id[j], NULL, 0);
            matriz_1[i][k]= *matrix_element;
            shmdt(matrix_element);
            j++;
        }
     
    for(int i = 0; i < 16; i++)
    {
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);
    }

    return;
}

void Suma(int matriz[4][4], int vec[4]){
    
     
    int   _shm_id[16];
    key_t _shm_key;
     
    struct shmid_ds shmidds[16];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
    int *matrix_element;
     
    int status;
    
    for(int i = 0; i < 16; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    } 

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
            {
                matrix_element = (int *) shmat(shm_id, NULL, 0);
                 
                *matrix_element= 0;
                 
                for(int k = 0; k < 4; k++)
                {
                    *matrix_element+= vec[i]*matriz[i][j];
                     
                    shmdt(matrix_element);
                 
                    exit(EXIT_SUCCESS);
                }
            }   
            else if(pid > 0)
            {
                for(int k = 0; k < 16; k++)
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
     
    //sleep(3);
     
    for(int i = 0; i < 16; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);
     
    //sleep(3);
     
    for(int i = 0, j = 0; i < 4; i++)
        for(int k = 0; k < 4; k++)
        {
            matrix_element = (int *) shmat(_shm_id[j], NULL, 0);
            vec[i]= *matrix_element;
            shmdt(matrix_element);
            j++;
        }
     
    for(int i = 0; i < 16; i++)
    {
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);
    }

    return;
}
