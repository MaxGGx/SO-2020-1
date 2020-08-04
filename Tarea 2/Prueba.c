#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

#define ESCRIBE 1
#define LEE 0

int fd0[2];
int fd1[2];
int fd2[2];
int fd3[2];
int fd4[2];

int pid1;
int pid2;

int aviso = 0;
int aviso2 = 0;

int valor;

int main()
{	
	
	pipe(fd0);
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	
	pid1 = fork();
	if (pid1 == 0)
	{
		while (aviso == 0)
		{
			close(fd0[ESCRIBE]); //Para leer aviso del padre
			close(fd1[ESCRIBE]); //Para leer valor del padre
			close(fd2[LEE]);     //Para enviar resultado al hijo 2

			read(fd0[LEE], &aviso, sizeof(int));

			read(fd1[LEE], &valor, sizeof(int));
			
			valor++;

			write(fd2[ESCRIBE], &valor, sizeof(int));
			
		}
		printf("TERMINE\n");
		exit(0);
	}

	pid2 = fork();
	if(pid2 == 0)
	{
		while (aviso2 == 0)
		{
			close(fd2[ESCRIBE]); //Para recibir valor del hijo
			close(fd3[ESCRIBE]); //Para leer aviso del padre
			close(fd4[LEE]);     //Para enviar resultado a padre

			read(fd3[LEE], &aviso2, sizeof(int));

			read(fd2[LEE], &valor, sizeof(int));

			valor *= 2;

			write(fd4[ESCRIBE], &valor, sizeof(int));
		}
		printf("TERMINE 2\n");
		exit(0);
	}

	while(1)
	{		
		printf("Ingresa un valor, se le sumara 1 y luego multiplicara por 2:\n");
		scanf("%d", &valor);

		if(valor == -1)
		{
			aviso = 1;
			aviso2 = 1;
			write(fd0[ESCRIBE], &aviso, sizeof(int));
			write(fd3[ESCRIBE], &aviso2, sizeof(int));
			break;

		}

		close(fd0[LEE]);
		close(fd1[LEE]);
		close(fd3[LEE]);
		close(fd4[ESCRIBE]);

		write(fd1[ESCRIBE], &valor, sizeof(int));

		write(fd0[ESCRIBE], &aviso, sizeof(int));

		write(fd3[ESCRIBE], &aviso2, sizeof(int));

		read(fd4[LEE], &valor, sizeof(int));

		printf("El valor es: %d\n", valor);
		valor = 0;
	}
	wait(&pid1);
	wait(&pid2);
	return 0;

}