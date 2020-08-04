@@@@@@@@@@@@@@@@@@@@@>Tarea 3 SO<@@@@@@@@@@@@@@@@@@@@@

Nombre: Iñaki Oyarzun
ROL: 201873620-1

Se asume: 

-El usuario siempre ingresara valores enteros positivos.

Descripción de la tarea:

Para esta tarea se implementa el proyecto en base al uso de threads por parte del uso de la libreria de java llamada java.lang.Thread la cual permite realizar la parte dos de la tarea.

Acerca de la parte 1. Los tiempos se entregan en milisegundos, esto para poder tener una mayor precision en los tiempos.

En la parte 2, se hace el uso de 2 threads para poder realizar la ejecución del programa, el método de implementacion consta de la creacion de una clase la cual implementa Runnable, que permite crear la hebra y el codigo que ejecutará, esta a su vez fue modificada por parte del alumno para que ambas pudiesen ejecutarse con un mismo código, es decir, un identificador entregado al inicio del thread le señalará que sector del codigo debe ejecutar. Este identificador corresponde a un array de dos valores, los cuales el primero sera el que indique la sección de codigo a ejecutar y el segundo corresponde al numero ingresado por el usuario. Este array es declarado al inicio para que pudiese ser recibido al inicio del thread (lineas 29-33).
Con ello igualmente, se declaran dos array[2] estáticos al inicio para que los threads puedan modificarlos y entregar el valor final para ser comparado (Siendo el valor 0, el numero encontrado y la posicion 1 la cantidad de divisores que tiene). De esta forma igualmente se evita la manipulacion de un mismo dato por parte de dos threads.

La forma de trabajo es similar a la de la parte uno de la tarea, en este caso se divide la carga de trabajo, es decir, antes un solo thread se encargaba de buscar todos los divisores de 1 a N, ahora cada thread hara la mitad del rango definido, es decir, el primer thread lo hará de 1 a N/2 y el segundo lo hará de N/2 o N/2+1 a N. finalmente el algoritmo compara los valores encontrados entre los dos threads y devuelve el mas alto. Finalmente entrega el tiempo de ejecucion del algoritmo en milisegundos para poder tener una mejor precision del tiempo.

Preguntas:

1.-¿A partir de qué número N, se empieza a notar una diferencia entre ambas implementaciones?
-La diferencia comienza a notarse por cuestión de milisegundos (aproximadamente 4 a 8 milisegundos) para cuando se aplica un rango de 50000, siendo bastante mas notorio para un rango de 10000000 con una diferencia aproximada de 24 segundos. 

2.-¿A qué se debe esto? Argumente.
-Esta diferencia se ve debido a que como se utilizan dos hebras, el algoritmo puede ejecutarse en dos partes, dividiendo la carga, permitiendo a diferencia de tener que verificar con una sola hebra todo el rango, dos pueden hacerlo en la mitad de tiempo teoricamente al entregarles a cada uno una mitad del mismo, asegurandose de comparar al final el valor y entregar el resultado. Esto obviamente dependerá del tipo de computador con el que se ejecute, ya que para casos en los que existan computadores con solo un thread disponible, el tiempo de ejecucion no se vera mejorado comparando los dos programas. Igualmente esta diferencia es a su vez por ser un rango igualmente alto, ya que se hace mas efectivo el uso del programa con hebras al notarse mas el tiempo que le lleva ejecutar la busqueda, ya que si se realiza en un rango pequeño, existirán casos en los que el uso de dos threads no sera efectivo.

Para el makefile basta con correr:

-> make

Luego para ejecutar la parte 1:
->make SH

Y para la parte 2:
->make CH

Finalmente para limpiar los archivos .class creados basta con:
->make clean 

@@@@@@@@@@@@@@@@@@@@@>FIN DEL README<@@@@@@@@@@@@@@@@@@@@@
