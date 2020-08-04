#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "lista3.h"


//NOMBRE FUNCION: InitCat()
//
//ENTRADA: 
//Lista simple vacia (ListaC*)
//
//SALIDA:
//Devuelve la misma lista, ya inicializada
//
//DESCRIPCION:
//Funcion que inicializa la lista simple
ListaC* InitCat(ListaC* lista)
{
	lista->cabeza = NULL;
	lista->longitud = 0;
	return lista;
}

//NOMBRE FUNCION: Init
//
//ENTRADA: Lista de listas vacía (Lista*)
//
//SALIDA:
//Devuelve la misma lista, ya inicializada
//
//DESCRIPCION:
//Funcion que inicializa la lista de listas
Lista* Init(Lista* lista)
{	
	lista->slabs = 0;
	lista->cant = 0;
	lista->cabeza = NULL;
	return lista;
}

//NOMBRE FUNCION: ClearLC
//
//ENTRADA: Lista simple (ListaC*) con datos
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que limpia las listas simples, no las libera completamente
void ClearLC(ListaC* libroc)
{
	NodoC* actual = libroc->cabeza;
	NodoC* next;
	while (actual != NULL)
	{
		next = actual->siguiente;
		free(actual);
		actual = next;
	}
	libroc->cabeza = NULL;
}

// A CONTINUACION: FUNCIONES QUE CREAN NODOS PARA LA LISTA DE LISTAS Y LA LISTA NORMAL

//NOMBRE FUNCION: CrearCat
//
//ENTRADA: 
//Char* que almacenara el nodo
//
//SALIDA:
//Retorna un nodo de la lista simple
//
//DESCRIPCION:
//Funcion que crea nodos para la lista simple de categorias 
NodoC* CrearCat(char* categoria)
{
	NodoC* nodo = (NodoC *)malloc(sizeof(NodoC));
	strncpy(nodo->cat.categoria, categoria, 120);
	nodo->cat.cant = 0;
	nodo->siguiente = NULL;
	return nodo;
}

//NOMBRE FUNCION: CrearNodo2
//
//ENTRADA: 
//Struct Libro
//
//SALIDA:
//Retorna un nodo de la lista de listas.
//
//DESCRIPCION:
//Funcion que crea nodos para la lista de listas de libros a partir del struct
Nodo* CrearNodo2(Libro libro)
{
	Nodo* nodo = (Nodo *)malloc(sizeof(Nodo));
	strncpy(nodo->libro.titulo, libro.titulo, 120);
	strncpy(nodo->libro.autor, libro.autor, 120);
	strncpy(nodo->libro.categoria, libro.categoria, 120);
	nodo->libro.anio = libro.anio;
	nodo->libro.pje = libro.pje;
	nodo->libro.promedio = 0;
	nodo->siguiente = NULL;
	nodo->abajo = NULL;
	return nodo;
}

//NOMBRE FUNCION: BuscaAnadeCat
//
//ENTRADA: 
//La lista simple (ListaC*), junto al char* categoria
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Esta funcion revisa si ya esta incluida la categoria que se entrega en la lista simple, para agregarla al final en caso de no estar
void BuscaAnadeCat(ListaC* listac, char* categoria)
{
	if(listac->cabeza == NULL)
	{
		NodoC* nodo = CrearCat(categoria);
		listac->longitud++;
		listac->cabeza = nodo;
		return;
	}
	NodoC* puntero = listac->cabeza;
	int cont = 0;
	while(puntero->siguiente)
	{
		if(strcmp(puntero->cat.categoria,categoria) == 0)
		{
			cont++;
		}
		puntero = puntero->siguiente;
	}
	if(strcmp(puntero->cat.categoria,categoria) == 0)
	{
		cont++;
	}
	if(cont>0)
	{
		return;
	}
	else
	{
		NodoC* nodo = CrearCat(categoria);
		listac->longitud++;
		puntero->siguiente = nodo;
	}

}

//NOMBRE FUNCION: ArmCat
//
//ENTRADA: 
//La lista simple (ListaC*) junto a la lista de listas (Lista*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//La funcion recorre la lista de listas de libros para obtener todas las categorias de la biblioteca y almacenarlas en la lista simple
void ArmaCat(ListaC* listac, Lista* lista)
{
	char str[120];

	Nodo* puntero = lista->cabeza;
	while(puntero->siguiente)
	{
		while(puntero->abajo)
		{
			strcpy(str, puntero->libro.categoria);
			str[strlen(str)-1]='\0';
			BuscaAnadeCat(listac, str);
			puntero = puntero->abajo;
		}
		strcpy(str, puntero->libro.categoria);
		str[strlen(str)-1]='\0';
		BuscaAnadeCat(listac, str);
		puntero = puntero->siguiente;
	}
	while(puntero->abajo)
	{
		strcpy(str, puntero->libro.categoria);
		str[strlen(str)-1]='\0';
		BuscaAnadeCat(listac, str);
		puntero = puntero->abajo;
	}
	strcpy(str, puntero->libro.categoria);
	str[strlen(str)-1]='\0';
	BuscaAnadeCat(listac, str);
}

//NOMBRE FUNCION: PrintCategorías
//
//ENTRADA: 
//Lista simple (ListaC*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que imprime las categorias de la lista simple de categorias
void PrintCategorias(ListaC* lista)
{
	printf("\nLa(s) Categoría(s) es/son:\n");
	NodoC* puntero = lista->cabeza;
	while(puntero->siguiente)
	{
		printf("->%s\n", puntero->cat.categoria);
		puntero = puntero->siguiente;
	}
	printf("->%s\n\nEn total son: %d categorías\n", puntero->cat.categoria, lista->longitud);
}

//NOMBRE FUNCION: CrearCategorias
//
//ENTRADA: 
//Lista simple (ListaC*) y el nombre de la carpeta (char*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que crea las carpetas de las categorias a partir de la lista de categorias y el nombre de la carpeta que contiene los txt
void CrearCategorias(ListaC* listac, char* carpeta)
{
	char str[120];
	chdir(carpeta);
	NodoC* puntero = listac->cabeza;
	while(puntero->siguiente)
	{
		strcpy(str, puntero->cat.categoria);
		mkdir(str,0777);
		puntero = puntero->siguiente;
	}
	strcpy(str, puntero->cat.categoria);
	mkdir(str,0777);
	chdir("..");
}

//NOMBRE FUNCION: CuentaCat
//
//ENTRADA: 
//Lista simple (ListaC*) y el nombre de la categoria (char*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que se encarga de recibir la categoria y la lista para verificar si esta presente para sumarle 1 en el nodo la seccion cant. Si no esta, lo agrega y le suma 1
void CuentaCat(ListaC* listac, char* categoria)
{
	if(listac->cabeza == NULL) //Si es que la lista esta vacía
	{
		NodoC* nodo = CrearCat(categoria);
		nodo->cat.cant++;
		listac->longitud++;
		listac->cabeza = nodo;
		return;
	}
	NodoC* puntero = listac->cabeza;
	while(puntero->siguiente)  //Recorro para ir buscando si ya esta creada la categoría
	{
		if(strcmp(puntero->cat.categoria,categoria) == 0) //Si la encuentro, le sumo 1 a su contador y termino
		{
			puntero->cat.cant++;
			return;
		}
		puntero = puntero->siguiente;
	}
	if(strcmp(puntero->cat.categoria,categoria) == 0) //Si llego al final de la lista y ese ultimo nodo coincide, sumo 1 y termino
	{
		puntero->cat.cant++;
		return;
	}
	else  //Si luego de recorrer todo no esta esa categoria en la lista, creo su nodo, lo añado y le sumo uno para terminar
	{
		NodoC* nodo = CrearCat(categoria);
		nodo->cat.cant++;
		listac->longitud++;
		puntero->siguiente = nodo;
		return;
	}

}

//NOMBRE FUNCION: AutorACat
//
//ENTRADA: 
//Lista de listas (Lista*), lista simple (ListaC*) y el nombre de la categria (char*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que se encarga de ver en cual carpeta ira cada autor y mover su carpeta a la categoria
void AutorACat(Lista* lista, ListaC* acat, char* carpeta)
{
	char str[1] = "/";
	char str2[120];      //Almacena categoria
	char str3[120];      //Almacena autor 
	//char str4[120];    //Almacena categoria mayor
	int  valor = -1;     //Permite comparar los valores
	chdir(carpeta);

	Nodo* puntero = lista->cabeza;
	Nodo* puntero2 = lista->cabeza;
	while (puntero->siguiente)
	{
		while(puntero2->abajo) //Este while al llegar al ultimo nodo, sale. Por no tener un siguiente
		{
			strcpy(str2, puntero->libro.categoria);
			str2[strlen(str2)-1] = '\0';
			CuentaCat(acat, str2);
			puntero2 = puntero2->abajo;
		}
		strcpy(str2, puntero->libro.categoria); //Por lo anterior, se debe repetir una vez más
		str2[strlen(str2)-1] = '\0';
		CuentaCat(acat, str2);
		NodoC* puntero3 = acat->cabeza;
		while (puntero3->siguiente)
		{
			if(puntero3->cat.cant >= valor)
			{
				valor = puntero3->cat.cant;
				strcpy(str2, puntero3->cat.categoria);
			}
			puntero3 = puntero3->siguiente;
		}
		if(puntero3->cat.cant >= valor)
		{
			valor = puntero3->cat.cant;
			strcpy(str2, puntero3->cat.categoria);
		}
		strcpy(str3, puntero->libro.autor);
		str3[strlen(str3)-1] = '\0';
		rename(str3, strncat(strncat(str2, str, 1), str3, strlen(str3)));
		valor = -1;
		ClearLC(acat);
		puntero = puntero->siguiente;
	}
	while(puntero2->abajo) //Este while al llegar al ultimo nodo, sale. Por no tener un siguiente
	{
		strcpy(str2, puntero->libro.categoria);
		str2[strlen(str2)-1] = '\0';
		CuentaCat(acat, str2);
		puntero2 = puntero2->abajo;
	}
	strcpy(str2, puntero->libro.categoria); //Por lo anterior, se debe repetir una vez más
	str2[strlen(str2)-1] = '\0';
	CuentaCat(acat, str2);
	NodoC* puntero3 = acat->cabeza;
	while (puntero3->siguiente)
	{
		if(puntero3->cat.cant >= valor)
		{
			valor = puntero3->cat.cant;
			strcpy(str2, puntero3->cat.categoria);
		}
		puntero3 = puntero3->siguiente;
	}
	if(puntero3->cat.cant >= valor)
	{
		valor = puntero3->cat.cant;
		strcpy(str2, puntero3->cat.categoria);
	}
	strcpy(str3, puntero->libro.autor);
	str3[strlen(str3)-1] = '\0';
	rename(str3, strncat(strncat(str2, str, 1), str3, strlen(str3)));
	chdir("..");
}

//NOMBRE FUNCION:CrearCarpetas
//
//ENTRADA:
//Lista de listas (Lista*) y el nombre de la carpeta (char*) 
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que construye las carpetas de cada autor e ingresa todos sus libros a dicha carpeta
void CrearCarpetas(Lista* lista, char* carpeta)
{
	char str[120]; //TITULOS
	char str2[120]; //AUTORES
	char str3[4] = ".txt";
	char str4[1]= "/";
	chdir(carpeta);
	Nodo* puntero = lista->cabeza;
	Nodo* puntero2 = lista->cabeza;
	while(puntero->siguiente)
	{
		strcpy(str2, puntero->libro.autor);
		str2[strlen(str2)-1] = '\0';
		mkdir(str2, 0777);
		while(puntero2->abajo)
		{
			strcpy(str, puntero2->libro.titulo); //Titulo
			str[strlen(str)-1]='\0';
			strncat(str, str3, 4); // Titulo.txt
			rename(str, strncat(strncat(str2, str4, 1),str ,strlen(str))); //libro.txt a autor/libro.txt
			strcpy(str2, puntero->libro.autor);
			str2[strlen(str2)-1] = '\0';
			puntero2 = puntero2->abajo;
		}
		strcpy(str, puntero2->libro.titulo); //Titulo
		str[strlen(str)-1]='\0';
		strncat(str, str3, 4); // Titulo.txt
		rename(str, strncat(strncat(str2, str4, 1),str ,strlen(str))); //libro.txt a autor/libro.txt
		puntero = puntero->siguiente;
		puntero2 = puntero;
	}
	strcpy(str2, puntero->libro.autor);
	str2[strlen(str2)-1] = '\0';
	mkdir(str2,0777);
	while(puntero2->abajo)
	{
		strcpy(str, puntero2->libro.titulo); //Titulo
		str[strlen(str)-1]='\0';
		strncat(str, str3, 4); // Titulo.txt
		rename(str, strncat(strncat(str2, str4, 1),str ,strlen(str))); //libro.txt a autor/libro.txt
		strcpy(str2, puntero->libro.autor);
		str2[strlen(str2)-1] = '\0';
		puntero2 = puntero2->abajo;
	}
	strcpy(str, puntero2->libro.titulo); //Titulo
	str[strlen(str)-1]='\0';
	strncat(str, str3, 4); // Titulo.txt
	rename(str, strncat(strncat(str2, str4, 1),str ,strlen(str))); //libro.txt a autor/libro.txt
	chdir("..");
}

//NOMBRE FUNCION:BuscaAnade
//
//ENTRADA:
//Lista de listas (Lista*) y struct Libro 
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que se encarga de crear la lista de listas a partir de los libros, organizando cada sublista como cada autor
void BuscaAnade(Lista* lista, Libro librito)
{
	Nodo* nodo = CrearNodo2(librito);
	if (lista->cabeza == NULL)  //Si esta vacia la lista, este sera el primer nodo
	{	
		
		lista->cabeza = nodo;
		lista->slabs++;
		lista->cant++;
		return;
	}
	Nodo* puntero = lista->cabeza;
	while(puntero->siguiente) //ya estando en la cabeza recuerda que es un nodo
	{
		if (strcmp(puntero->libro.autor, librito.autor) == 0)
		{
			
			if (puntero->abajo == NULL)
			{
				puntero->abajo = nodo;
				nodo->siguiente = puntero->siguiente;
				lista->cant++;
				return;
			}
			else
			{
				while(puntero->abajo)
				{
					puntero = puntero->abajo;
				}
				puntero->abajo = nodo;
				nodo->siguiente = puntero->siguiente;
				lista->cant++;
				return;
			}
		}
		puntero = puntero->siguiente;
	}
	//COMO VA A PARAR EN EL ULTIMO, NO ALCANZARA A COMPROBAR DE NUEVO. POR ESO LO
	//AÑADO UNA VEZ MÁS EL IF
	if (strcmp(puntero->libro.autor, librito.autor) == 0)
	{
			
		if (puntero->abajo == NULL)
		{
			puntero->abajo = nodo;
			nodo->siguiente = puntero->siguiente;
			lista->cant++;
			return;
		}
		else
		{
			while(puntero->abajo)
			{
				puntero = puntero->abajo;
			}
			puntero->abajo = nodo;
			nodo->siguiente = puntero->siguiente;
			lista->cant++;
			return;
		}
	}
	puntero->siguiente = nodo;
	lista->slabs++;
	lista->cant++;
}

//NOMBRE FUNCION:Orden
//
//ENTRADA: 
//Lista de listas(Lista*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que reordena la direccion de los punteros de cada nodo para terminar de conformar la estructura deseada con la lista de listas
void Orden(Lista* lista)
{
	Nodo* puntero1 = lista->cabeza;
	Nodo* puntero2 = lista->cabeza;
	while(puntero1->siguiente)
	{

		while(puntero2->abajo)
		{
			puntero2 = puntero2->abajo;
			puntero2->siguiente = puntero1->siguiente;

		}
		puntero1 = puntero1->siguiente;
		puntero2 = puntero1;

	}
	while(puntero2->abajo)
		{
			puntero2 = puntero2->abajo;
			puntero2->siguiente = puntero1->siguiente;

		}
}

//NOMBRE FUNCION: CalcPromedio
//
//ENTRADA: 
//Lista de listas (Lista*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que calcula el promedio de cada autor en la lista de listas agregando su promedio a la cabeza de cada sublista
void CalcPromedio(Lista* lista)
{
	int total = 0;  //irá contando la cantidad de puntos en total
	int cantidad = 0; //irá almacenando el total de libros
	Nodo* puntero = lista->cabeza;
	Nodo* puntero2 = lista->cabeza;
	while(puntero->siguiente)
	{
		while(puntero2->abajo)
		{
			total += puntero2->libro.pje;
			cantidad++;
			puntero2 = puntero2->abajo;
		}
		total += puntero2->libro.pje;
		cantidad++;
		puntero->libro.promedio = (total/cantidad);
		total = 0;
		cantidad = 0;
		puntero = puntero->siguiente;
		puntero2 = puntero;
	}
	while(puntero2->abajo)
	{
		total += puntero2->libro.pje;
		cantidad++;
		puntero2 = puntero2->abajo;
	}
	total += puntero2->libro.pje;
	cantidad++;
	puntero->libro.promedio = (total/cantidad);
	total = 0;
	cantidad = 0;
}

//NOMBRE FUNCION: ContarCant
//
//ENTRADA: 
//Lista de listas (Lista*)
//
//SALIDA:
//int que representa la cantidad de libros de la lista de listas
//
//DESCRIPCION:
//Funcion que retorna la cantidad de libros en la carpeta a partir de la lista de listas
int ContarCant(Lista* lista)
{
	return lista->cant;
}

//NOMBRE FUNCION: ContarSlabs
//
//ENTRADA: 
//Lista de listas (Lista*)
//
//SALIDA:
//int que representa la cantidad de sublistas
//
//DESCRIPCION:
//Funcion que retorna la cantidad de sublistas de la lista de listas, llamadas eslabones o slabs
int ContarSlabs(Lista* lista)
{
	return lista->slabs;
}

//NOMBRE FUNCION: PresentarAux
//
//ENTRADA: 
//Lista de listas (Lista*), nombre de la carpeta (char*), valor deseado (int)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que asiste a presentar, este revisa y compara los autores en la lista de listas con el valor y todos los autores que tiene la carpeta de categorias, si el promedio del autor calza, lo presenta por pantalla
void PresentarAux (Lista* lista, char* carpeta, int valor)
{
	ListaC* aux = (struct ListaC*)malloc(sizeof(struct ListaC));
	InitCat(aux);
	char str[120];				   //Autores
	struct dirent *de; 		       //Puntero del directorio de entrada
	DIR *dr = opendir(carpeta);	   // opendir() retorna un puntero del tipo DIR
	if (dr == NULL)
	{
		printf("No se ha podido abrir el directorio\n");
		return;
	}

	while ((de = readdir(dr)) != NULL)
	{
		if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
		{
			continue;	
		}
		else
		{		
			NodoC* nodo = CrearCat(de->d_name);
			if (aux->cabeza == NULL)
			{	
				aux->cabeza = nodo;
			}
			else
			{
				NodoC* puntero = aux->cabeza;
				while(puntero->siguiente)
				{
					puntero = puntero->siguiente;
				}
				puntero->siguiente = nodo;
			}

		}
	}
	closedir(dr);
	NodoC* puntero3 = aux->cabeza;
	Nodo*  puntero2 = lista->cabeza;
	while (puntero3->siguiente)
	{
		puntero2 = lista->cabeza;
		while(puntero2->siguiente)
		{
			strcpy(str, puntero2->libro.autor);
			str[strlen(str)-1]='\0';
			if (strcmp(str, puntero3->cat.categoria) == 0 && valor == puntero2->libro.promedio)
			{
				printf("->%s %d/10\n", str, valor);
			}
			puntero2 = puntero2->siguiente;
		}
		strcpy(str, puntero2->libro.autor);
		str[strlen(str)-1]='\0';
		if (strcmp(str, puntero3->cat.categoria) == 0 && valor == puntero2->libro.promedio)
		{
			printf("->%s %d/10\n", str, valor);
		}
		puntero3 = puntero3->siguiente;
	}
	puntero2 = lista->cabeza;
	while(puntero2->siguiente)
	{
		strcpy(str, puntero2->libro.autor);
		str[strlen(str)-1]='\0';
		if (strcmp(str, puntero3->cat.categoria) == 0 && valor == puntero2->libro.promedio)
		{
			printf("->%s %d/10\n", str, valor);
		}
		puntero2 = puntero2->siguiente;
	}
	strcpy(str, puntero2->libro.autor);
	str[strlen(str)-1]='\0';
	if (strcmp(str, puntero3->cat.categoria) == 0 && valor == puntero2->libro.promedio)
	{
		printf("->%s %d/10\n", str, valor);
		ClearLC(aux);
		free(aux);
		return;
	}
	ClearLC(aux);
	free(aux);
	return;
}

//NOMBRE FUNCION: Presentar
//
//ENTRADA:
//Lista de listas (Lista*) y el nombre de la carpeta de la biblioteca
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que se encarga de administrar la presentacion de autores de mayor a menor promedio de puntuacion 
void Presentar(Lista* lista, char* carpeta)
{
	printf("\nLos Autores ordenados de mayor a menor puntuacion son:\n");
	for (int i = 10; i > -1 ; --i)
	{
		PresentarAux(lista, carpeta, i);
	}
}

//NOMBRE FUNCION: PresentarLibro
//
//ENTRADA: 
//Lista de listas (Lista*) y el nombre dle titulo del libro (char*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que imprime por pantalla la informacion de un libro a partir del titulo y la lista de listas
void PresentarLibro(Lista* lista, char* titulo)
{
	char str[120];
	Nodo* puntero = lista->cabeza;
	while (puntero->siguiente)
	{
		strcpy(str, puntero->libro.titulo);
		str[strlen(str)-1] = '\0';
		if(strcmp(str , titulo) == 0)
		{
			printf("\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", titulo);
			printf("AUTOR: %sAÑO DE PUBLICACION: %d\nPUNTUACION: %d/10\n\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", puntero->libro.autor, puntero->libro.anio, puntero->libro.pje, titulo);
			return;
		}
		while(puntero->abajo)
		{
			puntero = puntero->abajo;
			strcpy(str, puntero->libro.titulo);
			str[strlen(str)-1] = '\0';
			if(strcmp(str , titulo) == 0)
			{
				printf("\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", titulo);
				printf("AUTOR: %sAÑO DE PUBLICACION: %d\nPUNTUACION: %d/10\n\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", puntero->libro.autor, puntero->libro.anio, puntero->libro.pje, titulo);
				return;
			}
		}
		puntero = puntero->siguiente;
	}
	strcpy(str, puntero->libro.titulo);
	str[strlen(str)-1] = '\0';
	if(strcmp(str , titulo) == 0)
	{
		printf("\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", titulo);
		printf("AUTOR: %sAÑO DE PUBLICACION: %d\nPUNTUACION: %d/10\n\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", puntero->libro.autor, puntero->libro.anio, puntero->libro.pje, titulo);
		return;
	}
	while(puntero->abajo)
	{
		puntero = puntero->abajo;
		strcpy(str, puntero->libro.titulo);
		str[strlen(str)-1] = '\0';
		if(strcmp(str , titulo) == 0)
		{
			printf("\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", titulo);
			printf("AUTOR: %sAÑO DE PUBLICACION: %d\nPUNTUACION: %d/10\n\n@@@@@@@@@@@@@@@@@@@@>%s<@@@@@@@@@@@@@@@@@@@@\n\n", puntero->libro.autor, puntero->libro.anio, puntero->libro.pje, titulo);
			return;
		}
	}
}

//NOMBRE FUNCION: RandCat
//
//ENTRADA: 
//Lista de listas (Lista*) y el nombre de la categoria (chhar*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Obtiene un libro al azar a partir de la categoria entregada y lo imprime
void RandCat(Lista* lista, char* categoria)
{
	char str[120];
	char str2[1] = "\n";
	strcpy(str, categoria);
	strncat(str, str2, 1);
	ListaC* aux = (struct ListaC*)malloc(sizeof(struct ListaC));
	InitCat(aux);
	NodoC* puntero2 = aux->cabeza;
	Nodo* puntero = lista->cabeza;
	while(puntero->siguiente)
	{
		if(strcmp(puntero->libro.categoria, str) == 0)
		{
			NodoC* nodo = CrearCat(puntero->libro.titulo);
			if (aux->cabeza == NULL)
			{	
				aux->cabeza = nodo;
				aux->longitud++;
			}
			else
			{
				puntero2 = aux->cabeza;
				while(puntero2->siguiente)
				{
					puntero2 = puntero2->siguiente;
					
				}
				puntero2->siguiente = nodo;
				aux->longitud++;
			} 
		}
		while(puntero->abajo)
		{
			puntero = puntero->abajo;
			if(strcmp(puntero->libro.categoria, str) == 0)
			{
				NodoC* nodo = CrearCat(puntero->libro.titulo);
				if (aux->cabeza == NULL)
				{	
					aux->cabeza = nodo;
					aux->longitud++;
				}
				else
				{
					puntero2 = aux->cabeza;
					while(puntero2->siguiente)
					{
						puntero2 = puntero2->siguiente;
					}
					puntero2->siguiente = nodo;
					aux->longitud++;
				} 
			}
		}
		puntero = puntero->siguiente;
	}
	if(strcmp(puntero->libro.categoria, str) == 0)
	{
		NodoC* nodo = CrearCat(puntero->libro.titulo);
		if (aux->cabeza == NULL)
		{	
			aux->cabeza = nodo;
			aux->longitud++;
		}
		else
		{
			puntero2 = aux->cabeza;
			while(puntero2->siguiente)
			{
				puntero2 = puntero2->siguiente;
			}
			puntero2->siguiente = nodo;
			aux->longitud++;
			
		} 
	}
	while(puntero->abajo)
	{
		puntero = puntero->abajo;
		if(strcmp(puntero->libro.categoria, str) == 0)
		{
			NodoC* nodo = CrearCat(puntero->libro.titulo);
			if (aux->cabeza == NULL)
			{	
				aux->cabeza = nodo;
				aux->longitud++;
			}
			else
			{
				puntero2 = aux->cabeza;
				while(puntero2->siguiente)
				{
					puntero2 = puntero2->siguiente;
				}
				puntero2->siguiente = nodo;
				aux->longitud++;
			} 
		}
	}
	srand(time(0));
	int final = rand() % aux->longitud;
	NodoC* puntero3 = aux->cabeza;
	for (int i = 0; i < final; ++i)
	{
		puntero3 = puntero3->siguiente;
	}
	strcpy(str, puntero3->cat.categoria);
	str[strlen(str)-1] = '\0';
	PresentarLibro(lista, str);
	ClearLC(aux);
	free(aux);
}

//NOMBRE FUNCION:RandLibro
//
//ENTRADA: 
//Lista de listas (Libro*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que imprime por pantalla un libro al azar
void RandLibro(Lista* lista)
{
	char str[120];
	srand(time(0));
	int final = rand() % lista->cant;
	int cont = 0;
	printf("%d", final);
	Nodo* puntero = lista->cabeza;
	while(puntero->siguiente)
	{
		
		if (cont == final)
		{
			strcpy(str, puntero->libro.titulo);
			str[strlen(str)-1] = '\0';
			PresentarLibro(lista, str);
		}
		cont++;
		while(puntero->abajo)
		{
			puntero = puntero->abajo;
			if(cont == final)
			{
				strcpy(str, puntero->libro.titulo);
				str[strlen(str)-1] = '\0';
				PresentarLibro(lista, str);
			}
			cont++;
		}
		puntero = puntero->siguiente;
	}
	if (cont == final)
	{
		strcpy(str, puntero->libro.titulo);
		str[strlen(str)-1] = '\0';
		PresentarLibro(lista, str);
	}
	cont++;
	while(puntero->abajo)
	{
		puntero = puntero->abajo;
		if(cont == final)
		{
			strcpy(str, puntero->libro.titulo);
			str[strlen(str)-1] = '\0';
			PresentarLibro(lista, str);
		}
		cont++;
	}
}

//NOMBRE FUNCION: ClearLista
//
//ENTRADA: 
//Lista de listas (Lista*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que limpia por completo la lista de listas y a la vez la elimina de la memoria
void ClearLista(Lista* lista)
{
	while (lista->cabeza != NULL)
	{
		Nodo* puntero = lista->cabeza;
		lista->cabeza = puntero->siguiente;
		Nodo* puntero2 = puntero;
		
		if (puntero->abajo)
		{
			while(puntero2 != NULL)
			{
				puntero2 = puntero->abajo;
				free(puntero);
				puntero = puntero2;
			}
		}
		free(puntero);
	}
	free(lista);
}

//NOMBRE FUNCION: PrintearElementos2
//
//ENTRADA: 
//Lista de listas (Lista*)
//
//SALIDA:
//No posee
//
//DESCRIPCION:
//Funcion que imprime por pantalla los elemtos de la lista de listas, diferenciando a la vez cada slab, antes debe pasar por la funcion Orden [Funcion creada solo para testear]
void PrintearElementos2(Lista* lista)
{
	int cont = 0;
	Nodo* puntero = lista->cabeza;
	while (puntero->siguiente)
	{
		printf("Slab: %d\n", cont);
		while(puntero->abajo)
		{
			printf("El titulo es: %sEl autor es: %sLa categoria es: %sEl puntaje es: %d\nEl promedio es: %d\n-------------------------------------------\n",puntero->libro.titulo, puntero->libro.autor,puntero->libro.categoria,puntero->libro.pje,puntero->libro.promedio);
			puntero = puntero->abajo;
		}
		printf("El titulo es: %sEl autor es: %sLa categoria es: %sEl puntaje es: %d\nEl promedio es: %d\n-------------------------------------------\n",puntero->libro.titulo, puntero->libro.autor,puntero->libro.categoria,puntero->libro.pje,puntero->libro.promedio);
		puntero = puntero->siguiente;
		cont++;
	}
	printf("Slab: %d\n", cont);
	//printf("El titulo es: %sEl autor es: %sLa categoria es: %sEl puntaje es: %d\nEl promedio es: %d\n-------------------------------------------\n",puntero->libro.titulo, puntero->libro.autor,puntero->libro.categoria,puntero->libro.pje,puntero->libro.promedio);
	while(puntero->abajo)
	{
		printf("El titulo es: %sEl autor es: %sLa categoria es: %sEl puntaje es: %d\nEl promedio es: %d\n-------------------------------------------\n",puntero->libro.titulo, puntero->libro.autor,puntero->libro.categoria,puntero->libro.pje,puntero->libro.promedio);
		puntero = puntero->abajo;
	}
	printf("El titulo es: %sEl autor es: %sLa categoria es: %sEl puntaje es: %d\nEl promedio es: %d\n-------------------------------------------\n",puntero->libro.titulo, puntero->libro.autor,puntero->libro.categoria,puntero->libro.pje,puntero->libro.promedio);	
}
