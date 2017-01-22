#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
 
int main(int argc, char **argv)
{
    int matrix_1_[3][3];
    int matrix_2_[3][3];
    int matrix_3_[3][3];
     
    int row_to_multiply;
    int col_to_multiply;
     
    int   _shm_id[9];
    key_t _shm_key;
     
    struct shmid_ds shmidds[9];
     
    int shm_id;
     
    pid_t pid;
    int   pid_counter = 0;
     
    int *matrix_element;
     
    int status;
     
    for(int i = 0; i < 9; i++)
    {
        _shm_key = ftok("./", i);
         
        if(_shm_key == -1)
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
         
        _shm_id[i] = shmget(_shm_key, sizeof(int), IPC_CREAT | SHM_R | SHM_W);
    }        
     
    printf("Matriz 1:\n");
     
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("Ingrese el valor para la posición [%d][%d]: ", i, j);
            scanf("%d", &matrix_1_[i][j]);
        }
    }
     
    printf("\nMatriz 2:\n");
     
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("Ingrese el valor para la posición [%d][%d]: ", i, j);
            scanf("%d", &matrix_2_[i][j]);
        }
    }
     
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            row_to_multiply = i;
            col_to_multiply = j;
            shm_id = _shm_id[pid_counter];
             
            pid = fork();
             
            if(pid == 0)
            {
                matrix_element = (int *) shmat(shm_id, NULL, 0);
                 
                *matrix_element= 0;
                 
                for(int k = 0; k < 3; k++)
                    *matrix_element += matrix_1_[row_to_multiply][k] * matrix_2_[k][col_to_multiply];
                     
                shmdt(matrix_element);
                 
                exit(EXIT_SUCCESS);
            }
            else if(pid > 0)
            {
                for(int k = 0; k < 9; k++)
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
     
    sleep(3);
     
    for(int i = 0; i < 9; i++)
        waitpid(WAIT_ANY, &status, WUNTRACED);
     
    sleep(3);
     
    for(int i = 0, j = 0; i < 3; i++)
        for(int k = 0; k < 3; k++)
        {
            matrix_element = (int *) shmat(_shm_id[j], NULL, 0);
            matrix_3_[i][k] = *matrix_element;
            shmdt(matrix_element);
            j++;
        }
         
    printf("\nMatriz 3:\n");
     
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", matrix_3_[i][j]);
         
        printf("\n");
    }
     
    for(int i = 0; i < 9; i++)
    {
        shmctl(_shm_id[i], IPC_RMID, &shmidds[i]);
    }
     
    return EXIT_SUCCESS;
}
