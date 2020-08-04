@@@@@@@@@@@@@@@@@@@@@>Tarea 4 SO<@@@@@@@@@@@@@@@@@@@@@

Nombre: Iñaki Oyarzun
ROL: 201873620-1

Se asume: 

-El usuario siempre ingresara valores enteros positivos.
-Cuando terminan de pasar todos los clientes, los cajeros dejan de ir al baño en caso de que en la iteracion final tenga que hacerlo. Es decir, si cuando pasa el ultimo cliente del cajero 4 y ese cajero justo necesita ir a lavarse las manos después de ese cliente, como es el final, no se realiza y se prioriza el termino del programa

Descripción de la tarea:

Para esta tarea se implementa el proyecto en base al uso de threads, locks, semaphores y events por parte del uso de la libreria threading de Python, al igual que la libreria time para simular los tiempos de espera junto con datetime para poder determinar los tiempos de entrada y salida de cada thread.

Al comienzo como se solicita en la tarea, se pide al usuario ingresar la cantidad de threads o clientes a simular, en donde a partir de ello se comienza con el sistema de tienda al entrar los primeros 30 clientes a través de un semáforo, el cual genera su propia lista de espera interna, a su vez los cajeros entran a su propio proceso el cual corresponde a habilitar la caja para comenzar a recibir los clientes. Una vez que los clientes compran, se dirigen a las cajas, en donde la forma para poder generar la cola de cada una y determinar la mas corta es a partir de la primera caja que se libere, de esta forma se distribuye la carga por cada caja para poder optimizar el tiempo total de ejecución del programa.

Finalmente, una vez que terminan los compradores de ser atendidos por el cajero, se aumenta un contador interno en cada cajero que indica la cantidad de clientes atendidos, el cual una vez llega a 5, se usa lock para ver el estado del baño y con ello entrar o sino, esperar atendiendo a otro cliente.

A medida que el cliente atraviesa una etapa esta se registra en una lista global, la cual al termino de ejecucion del algoritmo, solamente copia dichas lineas en el archivo de clientes, para los cajeros es lo mismo, registrando sus tiempo de ida y vuelta al baño.

Cabe destacar que el tiempo de ejecución del programa lleva aproximadamente 2 minutos para 80 personas, esto debido a que las esperas para cada thread de cliente en las etapas son altos, pero aún así el programa finaliza a pesar del tiempo de espera. Para que no se malinterprete como un programa que no funciona. 


@@@@@@@@@@@@@@@@@@@@@>FIN DEL README<@@@@@@@@@@@@@@@@@@@@@
