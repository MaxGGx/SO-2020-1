@@@@@@@@@@@@@@@@@@@@@>Tarea 1 SO<@@@@@@@@@@@@@@@@@@@@@

Nombre: Iñaki Oyarzun
ROL: 201873620-1

Se asume:

-Los .txt de los libros tendrán por titulo el nombre del libro.
-2 txt no tendran el mismo titulo.
-El orden de los utores al presentar la categoria de mayor a menor se debe realizar por la interfaz al no ser mencionada esta instruccion en el pdf.
-Los puntajes de los libros seran del 1 al 10, siendo numeros enteros.
-El programa solo se encargara de ordenar una carpeta liberia y para ordenar otra este debe volver a ejecutar
-Se toma como maximo de caracteres en las primeras 5 lineas como 120
-El usuario no ingresará mas de lo permitido por input en la interfaz
-En la seleccion numerica solo se ingresaran numeros y no texto
-Para navegar los menus la persona debe llegar al final de otro menu si es que entró.

Descripcion de la tarea:

Para esta tarea se realiza la implementacion de listas y con ello la estructuracion de otro tipo de listas, siendo las listas de listas, en las listas de listas lo que se realiza es almacenar todos los textos, ya clasificados por autor. y en las listas simples, solo se realiza para almacenar categorias o realizar comparaciones. Se agrega igualmente una carpeta con libros en txt con los que se probó este programa sin ningun problema, igualmente se incluye que el usuario si entra en un menú y quiere cambiar de este, debe llegar hasta el final del mismo. Para el make file basta con correr:

->make tarea1
->./tarea1

Y para borrar el ejecutable y el .o creado:

->make clean

A continuacion se muestra una representacion de la lista de listas graficamente:

-Se observa que cada nodo en la lista principal almacena 1 autor, mientras que hacia abajo, acumula los demas libros del mismo autor en donde cada nodo de la sublista igual apuntara al autor siguiente en su primer libro

-> Libro AUTOR 1-> Libro AUTOR 2->...->NULL
       |         /\   |
       v         |    v
  Libro2 AUTOR 1-    NULL
  	   |
  	   v
  	  NULL

@@@@@@@@@@@@@@@@@@@@@>FIN DEL README<@@@@@@@@@@@@@@@@@@@@@
