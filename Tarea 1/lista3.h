#ifndef LISTA3_H
#define LISTA3_H

//A CONTINUACION SE PRESENTAN LOS STRUCTS PARA PODER DEFINIR LAS LISTAS QUE SE ENCARGARAN DE ORDENAR Y REALIZAR LOS MANEJOS DE LOS TEXTOS
//LISTAS QUE ALMACENAN LIBROS , SERÁ UNA LISTA CON SUBLISTAS HACIA ABAJO
typedef struct Libro
{
	char titulo[120];
	char autor[120];
	char categoria[120];
	int anio;
	int pje;
	int promedio;
} Libro;

typedef struct Nodo 
{
	Libro libro;
	struct Nodo* siguiente;
	struct Nodo* abajo;
} Nodo;

typedef struct Lista 
{
	Nodo* cabeza;
	int slabs; //slabs son cada autor que hay
	int cant; //cant me dice cuantos libros hay
} Lista;


//PARA CATEGORIAS , SERÁ UNA LISTA SIMPLE
typedef struct Cat
{
	char categoria[120]; //Se usara igualmente para poder añadir nombres
	int cant;			 //Se usa para ver que categoria enviar autores
} Cat;


typedef struct NodoC
{
	Cat cat;
	struct NodoC* siguiente;
} NodoC;

typedef struct ListaC
{
	NodoC* cabeza;
	int longitud;
} ListaC;

ListaC* InitCat(ListaC*);
Lista* Init(Lista*);
void ClearLC(ListaC*);
NodoC* CrearCat(char*);
Nodo* CrearNodo2(Libro);
void BuscaAnadeCat(ListaC*, char*);
void ArmaCat(ListaC*, Lista*);
void PrintCategorias(ListaC*);
void CrearCategorias(ListaC*, char*);
void CuentaCat(ListaC*, char*);
void AutorACat(Lista*, ListaC*, char*);
void CrearCarpetas(Lista*, char*);
void BuscaAnade(Lista*, Libro);
void Orden(Lista*);
void CalcPromedio(Lista*);
int ContarCant(Lista*);
int ContarSlabs(Lista*);
void PresentarAux (Lista*, char*, int);
void Presentar(Lista*, char*);
void PresentarLibro(Lista*, char*);
void RandCat(Lista*, char*);
void RandLibro(Lista*);
void ClearLista(Lista*);
void PrintearElementos2(Lista*);

#endif