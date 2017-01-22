#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int leer_car();

int main (int argc, char *argv[])
{
	int shmid, *variable;
	key_t llave;

	llave= ftok(argv[0],'k');

	if ((shmid=shmget(llave,sizeof(int),IPC_CREAT|0600))==-1)
	{
		perror("Error en shmget");
		exit(-1);
	}

	while(1)
	{
		printf("\nIntroduzca m para modificar el valor \n v para visualizar \n t para terminar:\n ");
		
		switch(leer_car())
		{
			case 't':
			shmctl(shmid,IPC_RMID,0);
			break;

			case 'v':
			printf("\n variable= %d\n",*variable);
			break;

			case 'm':
			printf("Nuevo valor:");
			scanf("%d",variable);
			break;

			default:
			printf("valor incorrecto");
			break;
		}
	}
}

int leer_car()
{
	char letra;
	char almacen[80];

	scanf("%s",almacen);
	sscanf(almacen,"%c",&letra);
	return letra;
}
