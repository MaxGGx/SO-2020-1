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

#define total 0
#define	time0 1
#define	posx0 2
#define posy0 3
#define time1 4
#define posx1 5 
#define posy1 6
#define time2 7
#define posx2 8
#define posy2 9

int tabla[5][5] = {0};
int topos[10] = {0};

int puntaje = 0;

int fd1[2];
int fd2[2];
int fd3[2];
int fd4[2];
int fd5[2];
int fd6[2];
int fd7[2];

int pid1;
int pid2;
int pid3;

pid_t wpid;
int status = 0;

int aviso = 0;
int aviso2 = 0;
int aviso3 = 0;

int MR = 15; //Indica los movimientos restantes

void initTopos()
{
	topos[posx0] = 0;
	topos[posy0] = 0;
	topos[posx1] = 0;
	topos[posy1] = 0;
	topos[posx2] = 0;
	topos[posy2] = 0;
	topos[time0] = -1;
	topos[time1] = -1;
	topos[time2] = -1;
}

//Funcion que grafica a los topos dentro de la tabla de juego
void grafica()
{
	if(topos[time0] != -1)
	{
		tabla[topos[posx0]][topos[posy0]] = topos[time0];
	}
	if(topos[time1] != -1)
	{
		tabla[topos[posx1]][topos[posy1]] = topos[time1];
	}
	if(topos[time2] != -1)
	{
		tabla[topos[posx2]][topos[posy2]] = topos[time2];
	}
	for(int x = 0 ; x<5 ; x++)
	{
		for(int y = 0 ; y<5 ; y++)
		{
			printf("-%d-",tabla[x][y]);
		}
		printf("\n");
	}
}

//Funcion que busca una posicion vacia para ubicar al topo
void armapos(int numtopo)
{
	int x = rand()%5;
	int y = rand()%5;

	while (tabla[x][y] != 0 ) //Itera hasta obtener una posicion que no este ocupada
	{
		x = rand()%5;
		y = rand()%5;

	}
	if (numtopo == 0)
	{
		topos[posx0] = x;
		topos[posy0] = y;
	}
	else if (numtopo == 1)
	{
		topos[posx1] = x;
		topos[posy1] = y; 
	}
	else if (numtopo == 2)
	{
		topos[posx2] = x;
		topos[posy2] = y;
	}
}

//Funcion que determina la cantidad de topos que saldran en la iteracion proxima
void cantidadtopos()
{
	int valor;
	valor = rand()%4;  //INDICARA LA CANTIDAD DE TOPOS
	if (valor == 0)
	{
		topos[total] = 0;
	}
	else
		topos[total] = valor;
}

//Funcion que determina la cantidad de iteraciones de vida que tendra cada topo
void iteraciones()
{
	int valor;
	if(topos[total] == 1)
	{
		valor = rand()%4;
		if (valor == 0) {valor++;}
		topos[time0] = valor;

	}
	if(topos[total] == 2)
	{
		valor = rand()%4;
		if (valor == 0) {valor++;}
		topos[time0] = valor;

		valor = rand()%4;
		if (valor == 0) {valor++;}
		topos[time1] = valor;
	}
	if (topos[total] == 3)
	{
		valor = rand()%4;
		if (valor == 0) {valor++;}
		topos[time0] = valor;

		valor = rand()%4;
		if (valor == 0) {valor++;}
		topos[time1] = valor;
	
		valor = rand()%4;
		if (valor == 0) {valor++;}
		topos[time2] = valor;
	}
}

//Funcion que determinara las posiciones de los topos
void posiciones()
{
	if (topos[total] == 1)
	{
		armapos(0);
	}
	else if (topos[total] == 2)
	{
		armapos(0);
		armapos(1);
	}
	else if (topos[total] == 3)
	{
		armapos(0);
		armapos(1);
		armapos(2);
	}
}

//Funcion que otorga el puntaje y determina si las posiciones golpeadas fueron correctas o no
void whack(int posx, int posy)
{
	if (tabla[posx][posy] != 0 )
	{
		if (tabla[posx][posy] == 3)
		{
			puntaje ++;
		}
		else if (tabla[posx][posy] == 2)
		{
			puntaje += 3;
		}
		else if (tabla[posx][posy] == 1)
		{
			puntaje+=5;
		}
		tabla[posx][posy] = 0;
		printf("Le has dado a un topo!\n");
	}
	else
		printf("No le diste a ninguno!\n");
}


//Funcion de prueba que me muestra los topos creados por los otros procesos
void muestratopo()
{
	printf("--INFO TOPOS--\nTotal:%d\n\n--TOPO 1--\nTiempo:%d\nX:%d\nY:%d\n\n--TOPO 2--\nTiempo:%d\nX:%d\nY:%d\n\n--TOPO 3--\nTiempo:%d\nX:%d\nY:%d\n\n",topos[total],topos[time0],topos[posx0],topos[posy0],topos[time1],topos[posx1],topos[posy1],topos[time2],topos[posx2],topos[posy2]);
}

//Funcion que actualiza la tabla restando en una iteracion el tiempo de los topos
void update()
{
	for (int o = 0 ; o<5 ; o++)
	{
		for(int p = 0 ; p<5 ; p++)
		{
			if (tabla[o][p] != 0)
			{
				tabla[o][p]--;
			}
		}
	}
}

int main()
{
	int ans;
	int ansx;
	int ansy;

	srand(time(NULL));

	initTopos();

	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	pipe(fd5);
	pipe(fd6);
	pipe(fd7);
	
	pid1 = fork();
	if(pid1 == 0)
	{
		srand(time(NULL));
		while(aviso == 0)
		{
			close(fd1[ESCRIBE]); //Para leer aviso del padre
			close(fd2[ESCRIBE]); //Para leer el topo del padre
			close(fd3[LEE]);     //Para enviar el resultado al hijo 2

			if(aviso == 1){break;}

			read(fd2[LEE], &topos, sizeof(int)*10);

			initTopos();

			cantidadtopos();

			write(fd3[ESCRIBE], &topos, sizeof(int)*10);
			read(fd1[LEE], &aviso, sizeof(int));
		}
		exit(0);
	}

	pid2 = fork();
	if (pid2 == 0)
	{
		srand(time(NULL));
		while(aviso2 == 0)
		{
			close(fd3[ESCRIBE]); //Para recibir topo del hijo
			close(fd4[ESCRIBE]); //Para recibir aviso del padre
			close(fd5[LEE]);     //Para enviar resultado a hijo 3

			if(aviso2 == 1){break;}

			read(fd3[LEE], &topos, sizeof(int)*10);

			iteraciones();

			write(fd5[ESCRIBE], &topos, sizeof(int)*10);

			read(fd4[LEE], &aviso2, sizeof(int));
		}
		exit(0);
	}

	pid3 = fork();
	if (pid3 == 0)
	{
		srand(time(NULL));
		while(aviso3 == 0)
		{
			close(fd5[ESCRIBE]); //Para recibir topo del hijo 2
			close(fd6[ESCRIBE]); //Para recibir aviso del padre
			close(fd7[LEE]);     //Para enviar la respuesta final

			if(aviso3 == 1){break;}

			read(fd5[LEE], &topos, sizeof(int)*10);

			posiciones();

			write(fd7[ESCRIBE], &topos, sizeof(int)*10);
			read(fd6[LEE], &aviso3, sizeof(int));
		}
		exit(0);
	}
	
	while(1)
	{
		printf("Bienvenido al juego!\nSelecciona la modalidad:\n1 - Juego Normal\n2 - Juego Rápido (AUTOMATICO)\n3 - Salir\n\nIngresa el número a continuación:\n");
		scanf("%d", &ans);

		for(int x = 0 ; x<5 ; x++)
		{
			for(int y = 0 ; y<5  ; y++)
			{
				tabla[x][y] = 0;
			}
		}

		if(ans == 1)
		{
			printf("\nCOMIENZA EL JUEGO!!\n\n");

			while(MR>0)
			{
				printf("Movimientos restantes: %d\n", MR);
				close(fd1[LEE]);
				close(fd4[LEE]);
				close(fd6[LEE]);
				close(fd2[LEE]);
				close(fd7[ESCRIBE]);

				write(fd1[ESCRIBE], &aviso, sizeof(int));

				write(fd2[ESCRIBE], &topos, sizeof(int)*10);

				write(fd4[ESCRIBE], &aviso2, sizeof(int));

				write(fd6[ESCRIBE], &aviso3, sizeof(int));

				read(fd7[LEE], &topos, sizeof(int)*10);

				grafica();
			
				printf("Elige una posicion x para golpear! (0-4):\n");
				scanf("%d",&ansx);
			
				printf("Elige una posicion y para golpear! (0-4):\n");
				scanf("%d",&ansy);
				
				printf("\n");

				whack(ansx,ansy);

				update();
				
				printf("\n\n");
				MR--;
				
			}
			printf("Puntaje Final: %d\n\n", puntaje);
			MR = 15;
			puntaje = 0;
		}
		if(ans == 2)
		{
			printf("A continuacion se presentará de forma automatica el juego:\n\n");

			printf("\nCOMIENZA EL JUEGO AUTOMATICO!!\n\n");

			while(MR>0)
			{
				printf("Movimientos restantes: %d\n", MR);
				close(fd1[LEE]);
				close(fd4[LEE]);
				close(fd6[LEE]);
				close(fd2[LEE]);
				close(fd7[ESCRIBE]);

				write(fd1[ESCRIBE], &aviso, sizeof(int));

				write(fd2[ESCRIBE], &topos, sizeof(int)*10);

				write(fd4[ESCRIBE], &aviso2, sizeof(int));

				write(fd6[ESCRIBE], &aviso3, sizeof(int));

				read(fd7[LEE], &topos, sizeof(int)*10);

				grafica();

				ansx = (rand()*rand())%5;
				if (ansx < 0) {ansx *= -1;}
				ansy = (rand()*rand()*rand())%5;
				if (ansy < 0) {ansy *= -1;}

				printf("Posición (x,y) elegida (%d , %d)\n\n", ansx, ansy);

				whack(ansx, ansy);

				update();

				printf("\n\n");
				MR--;
			}
			printf("Puntaje final BOT: %d\n\n", puntaje);
			MR = 15;
			puntaje = 0;
		}

		if (ans == 3)
		{
			aviso = 1;
			aviso2 = 1;
			aviso3 = 1;
			write(fd1[ESCRIBE], &aviso, sizeof(int));
			write(fd4[ESCRIBE], &aviso2, sizeof(int));
			write(fd6[ESCRIBE], &aviso3, sizeof(int));
			write(fd2[ESCRIBE], &topos, sizeof(int)*10);
			printf("Gracias por jugar!\n");
			return 0;
		}
	}
}

