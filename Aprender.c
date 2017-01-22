#include <stdio.h>
#include"funciones.h"

int main(int argc, char **argv)
{
    int vec_1[4]={1,-1,-1,1};
    int vec_2[4]={-1,1,-1,1};
    int vec_3[4]={-1,-1,1,-1};

    int matriz_1[4][4];
    int matriz_2[4][4];
    int matriz_3[4][4];
    int I[4][4];

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if(i==j)
                I[i][j]=1;
            else
                I[i][j]=0;
        }
    }
    
    Multi(vec_1,matriz_1); 
    Multi(vec_2,matriz_2);
    Multi(vec_3,matriz_3);
    Rest(matriz_1,I);
    Rest(matriz_2,I);
    Rest(matriz_3,I);
    Sum(matriz_1,matriz_2);
    Sum(matriz_1,matriz_3);

    printf("\nMatriz:\n");
     
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            printf("    %d ", matriz_1[i][j]);
         
        printf("\n");
    }  

    int vect_prueba[4]={-1,-1,1,-1};

    printf("\n El Vector inicial es: [");
    for(int j = 0; j < 4; j++)
            printf("%d,", vect_prueba[j]);
    printf("]\n");
    Suma(matriz_1,vect_prueba);

    printf("\n El Vector  final es: [");
    for(int j = 0; j < 4; j++)
            printf("%d,", vect_prueba[j]);
    printf("]\n");    
}
