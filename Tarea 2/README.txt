@@@@@@@@@@@@@@@@@@@@@>Tarea 2 SO<@@@@@@@@@@@@@@@@@@@@@
# Opinion del autor en el git: Tarea con complicaciones, se hizo dos veces gracias a un "compañero" que puso una pregunta que jodió lo asumido. Proximamente se subira la otra opción para abordar el problema.
Nombre: Iñaki Oyarzun


Se asume: 

-El usuario siempre ingresara valores enteros positivos.
-El juego tiene una duracion de 15 iteraciones o movimientos, donde en cada iteracion pueden salir de 0-3 topos.

Descripción de la tarea:

Para esta tarea se implementa el proyecto en base al uso de fork y pipes para la comunicacion de procesos. Se subdivide dentro del programa las funciones a utilizar y desde ahi son llamadas para su uso. Junto a ello se utiliza un array para poder facilitar el proceso de creacion de topos junto a variables definidas en el principio del codigo para identificar facilmente las posiciones. 

Junto a ello se implementa un sistema de puntaje, el cual cuando se golpea a un topo que le queda 1 iteracion restante para desaparecer se otorgan 5 puntos, para el que le quedan 2 se entregan 3 puntos y para el que le quedan 3 se entrega 1 punto. Mostrando al final el puntaje obtenido. La duracion restante del topo se señala con un numero dentro de la tabla, luego, si no se golpea, ira bajando su duracion en tabla hasta desaparecer.

Por otro lado, para realizar la posicion del golpe es de la forma (x,y), siendo x la fila del 0-4 y la columna del 0-4.

Para el makefile basta con correr:

->make tarea2
->./tarea2

Y para borrar el ejecutable y el .o creado:
->make clean 

@@@@@@@@@@@@@@@@@@@@@>FIN DEL README<@@@@@@@@@@@@@@@@@@@@@
