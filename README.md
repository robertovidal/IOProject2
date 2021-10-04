# IOPROJECT1
Estudiantes:
Jose Pablo Fernández Cubillo, 2019047740
Roberto Vidal Patiño, 2019065537

Primero es necesario tener instalado Latex con
todas sus funcionalidades, para ello podemos
hacerlo con el siguiente comando:

sudo apt install texlive-full

Para compilar el proyecto lo único que se debe hacer
es ingresar el comando make en la consola.

Para correr el programa hay dos formas:

./abb -X

El programa resolverá un solo caso aleatorio del
problema de los Árboles Binarios de Búsqueda Óptimos
con un algoritmo de programación dinámica y un algoritmo
greedy. El árbol tiene 6 llaves. Cada llave tendrá sus
probabilidades aleatorias y tendrá un valor ASCII
asignado que va de forma ascendente. Se despliega un pdf
hecho en Latex con los resultados.

./abb -E=n

En este caso n debe ser un número entero positivo
distinto de 0. El programa resolverá 10n casos
diferentes del problema de los Árboles Binarios de
Búsqueda Óptimos con un algoritmo de programación
dinámica y un algoritmo greedy. Las llaves del árbol
van de 10 hasta 100. Para cada uno de los n casos en la
cantidad de llaves, se generarán aleatoriamente las
probabilidades de cada llave, y la suma de estas
probabilidades debe ser 1. Se muestran los resultados
de ejecución de los dos algoritmos con tablas de
promedios de tiempo de ejecución y para el greedy
se coloca también una tabla con los porcentajes de éxito.

Si el comando se coloca mal o no se coloca ninguno
de los dos el programa despliega un tipo de ayuda
que indica al usuario cómo es que se utilizan los
comandos.