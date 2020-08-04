#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "lista3.h"
#define Buffer 100


//NOMBRE FUNCION: obtenerDatos
//
//ENTRADA: 
//Nombre del archivo (char*), nombre de la carpeta (char*) y la lista de listas (Libros*)
//
//SALIDA:
//Retorna un entero para comprobar que si funcionó (int)
//
//DESCRIPCION:
//Funcion que se encarga de leer los txt para poder ver sus primeras 5 lineas, crear un struct libro y añadirlo a la lista de listas
int obtenerDatos(char* nombre, char* carpeta, Lista* libros)
{
	Libro librito;
	FILE *fp;
	char str[120];
	char str2[2];

	chdir(carpeta);

	fp = fopen(nombre, "r");
	if (fp == NULL)
	{
		printf("No se pudo abrir el archivo %s\n", nombre);
		return 1;
	}
	int count = 0;
	while (fgets(str, 120, fp) != NULL)
	{
  		if (count == 0)
       	{
   			strncpy(librito.titulo, str, 120);
        }
        else if (count == 1)
        {
        	strncpy(librito.autor, str, 120);
        }
        else if (count == 2)
        {
        	strncpy(librito.categoria, str, 120);
        }
        else if (count == 3)
        {
        	librito.anio = atoi(str);
        }
        else if (count == 4)
        {
        	if (strlen(str) == 5)
        	{
        		strncpy(str2, str, 1);
        		librito.pje = atoi(str2);
        	}
        	else
        	{
        		librito.pje =  10;
        	}
        	
        }
       	count++;
	}
	BuscaAnade(libros, librito);
	fclose(fp);
	return 0;

}

//NOMBRE FUNCION: navegar
//
//ENTRADA: 
//Nombre de la carpeta (char*), lista de listas (Libros*), valor (int)
//
//SALIDA:
//Retorna un entero para comprobar que si funcionó
//
//DESCRIPCION:
//Entra a la carpeta de la biblioteca y obtiene el nombre de los txt y en caso contrario, puede imprimir por pantalla los datos que lee, quitando 4 caracteres finales
int navegar(char* carpeta, Lista* libros, int valor)
{
	struct dirent *de; 		       //Puntero del directorio de entrada
	DIR *dr = opendir(carpeta);	   // opendir() retorna un puntero del tipo DIR
	char lib[120];

	if (dr == NULL)
	{
		printf("No se ha podido abrir el directorio\n");
		return 0;
	}

	while ((de = readdir(dr)) != NULL)
	{
		if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
		{
			continue;	
		}
		else if(valor == 1) //Si es uno, quiere decir que aun no esta organizada la base de libros
		{
			obtenerDatos(de->d_name, carpeta, libros);
		}
		else if(valor == 2) //En cambio, si es dos, entonces puedo entrar solo para mostrar nombres
		{
			strcpy(lib, de->d_name);
			lib[strlen(lib)-1] = '\0';
			lib[strlen(lib)-1] = '\0';
			lib[strlen(lib)-1] = '\0';
			lib[strlen(lib)-1] = '\0';
			printf("->%s\n", lib);
		}
	}
	closedir(dr);

	return 1;
}

int main()
{
	Lista* libros = (struct Lista*)malloc(sizeof(struct Lista));
	Init(libros);
	ListaC* categorias = (struct ListaC*)malloc(sizeof(struct ListaC));
	InitCat(categorias);
	ListaC* auxiliar = (struct ListaC*)malloc(sizeof(struct ListaC*));
	InitCat(auxiliar);
	int men;
	int o = 0;
	char temp;
	char carpeta[Buffer]; //Almacena el nombre de la carpeta de la libreria
	char carpeta2[Buffer];//Almacena el nombte de la carpeta de categoria dentro de la libreria
	char carpeta3[Buffer];//Almacena el nombre de la carpeta del autor dentro de la categoria
	char libro[Buffer];   //Almacena el nombre del libro que se desea ver
	
	while (o == 0)
	{	
		printf("\nAntes de comenzar. Ingrese el nombre de la carpeta con los libros en .txt: \n");
		scanf("%c", &temp);
		scanf("%[^\n]", carpeta);
		DIR* dir = opendir(carpeta);
		if(dir)
		{
			o++;
		}
		else
		{
			printf("El directorio no existe!, asegurate de escribirlo bien respetando Mayusculas y minusculas");
		}
	}
	navegar(carpeta, libros, 1);									//Recorre los txt y los ordena en libros
	Orden(libros); 													//Ordena los libros de la forma deseada
	CrearCarpetas(libros, carpeta); 								//Crea las carpetas con los autores e ingresa los txt
	ArmaCat(categorias, libros); 									//Analiza los txt y obtiene las diferentes categorias que existen
	CrearCategorias(categorias, carpeta); 							//Crea las carpetas de categorias junto a las carpetas de autores 
	CalcPromedio(libros); 											//Calcula el promedio de puntaje de cada autor en la lista principal de libros en txt
	AutorACat(libros, auxiliar, carpeta); 							//Introduce las carpetas de autores a las carpetas de categorias, luego de ver a cual pertenecen 
	while(1)
	{
		printf("\nSeleccione a continuación:\n1)Ver informacion de un Libro\n2)Libro al azar por categoría\n3)Libro al azar\n0) Salir\n");
		scanf("%c", &temp);
		scanf("%d", &men);
		if (men == 1)
		{
			PrintCategorias(categorias); 									//Imprime las categorias que estan [INTERFAZ]
			printf("\nEscriba la categoria que desea ver a continuación: \n");
			scanf("%c", &temp);
			scanf("%[^\n]", carpeta2);
			chdir(carpeta);
			Presentar(libros, carpeta2);  									//Entra a la categoria e imprime los autores que estan en la categoria ordenados de mayor a menor
			printf("\nSeleccione el autor que desea observar escribiendo solo su nombre: \n");
			scanf("%c", &temp);
			scanf("%[^\n]", carpeta3);
			chdir(carpeta2);
			printf("\nLos libros de %s son:\n", carpeta3);
			navegar(carpeta3, libros, 2);
			printf("\nSeleccione el libro que desea observar, escribiendo su título: \n");
			scanf("%c", &temp);
			scanf("%[^\n]", libro);
			PresentarLibro(libros, libro);
			printf("Presione enter para volver al menú principal:\n");
			scanf("%c", &temp);
			scanf("%[^\n]", libro);
			chdir("..");
			chdir("..");
		} 
		else if (men == 2)
		{
			PrintCategorias(categorias); 									//Imprime las categorias que estan [INTERFAZ]
			printf("\nEscriba la categoria deseada para el libro al azar: \n");
			scanf("%c", &temp);
			scanf("%[^\n]", carpeta2);
			printf("\nEl libro elegido es:\n");
			RandCat(libros, carpeta2);
			printf("Presione enter para volver al menú principal:\n");
			scanf("%c", &temp);
			scanf("%[^\n]", libro);
		}
		else if (men == 3)
		{
			RandLibro(libros);
			printf("Presione enter para volver al menú principal:\n");
			scanf("%c", &temp);
			scanf("%[^\n]", libro);
		}
		else if (men == 0) 
		{
			ClearLC(categorias);
			free(categorias);
			ClearLC(auxiliar);
			free(auxiliar);
			ClearLista(libros);
			return 0;
		}
		else printf("Ingrese una opción válida\n");
	}
return 0;	
}