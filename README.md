# Letras
PRACTICA REALIZADA POR:
Antonio José Blánquez Pérez
2ºD ESTRUCTURA DE DATOS
-----------------------------------------------
Las directrices de esta práctica pedian realizar un programa llamado letras que es la implementación del juego de letras del programa Cifras y Letras. Para ello se han de implementar tres módulos a parte del programa principal. En mi caso se va a encontrar tres archivos .h y un .cpp, además de los ficheros de diccionario y de letras. Pasemos a repasar qué y como se ha hecho cada archivo:

-Ficheros de diccionario: he incluido 5 idiomas diferentes y d1000 que era uno que se daba de prueba. Obviamente no me he confeccionado yo esos ficheros(de entre 60000 y 80000 palabras) si no que me he ayudado de los siguientes enlaces:
	*DICCIONARIOS DE PALABRAS: http://www.gwicks.net/dictionaries.htm
	*QUITAR TILDES Y SIMBOLOS: http://www.texto.kom.gt/removertildesyacentos.htm

-Ficheros de letras: en este caso he decidido incluir dos archivos haciendo con ellos una elección de la dificultad, confeccionando el dificil añadiendo letras raras y quitando letras comunes de la bolsa.

-letras.cpp: aquí se incluye la implementacion del programa a través de las funciones de los módulos .h, por lo que no tiene mayor interés. Si destacaré que la jugabilidad está cuidada con filtros para asegurar la correcta entrada de datos y con la posibilidad de pasar si no se encuentra ninguna palabra.

-conjuntoletras.h: en este archivo está implementada la clase ConjuntoLetras, que pretende ser una estructura que contenga para cada letra cuántas veces debe de aparecer en la bolsa y qué puntuacion tiene. El conjunto está implementado mediante un map, ya que se puede entender que los campos repeticiones y puntuación son atributos de cada letra. Así que un char va a ser la key y un struct, que incluye repeticiones y puntuacion, será el mapped type. La implementación de las funciones no tiene demasiado interés.

-bolsaletras.h: en este archivo está implementada la clase BolsaLetras, que es un simple vector de char. Se construye pasándole como parámetro un ConjuntoLetras y se llama a la función privada llenar que mete al vector todas las letras tantas veces como indique su valor repeticiones. La otra función pública es sacarLetras, que devuelve un vector de char (para el programa principal) que incluye tantas letras aleatorias de la bolsa como represente el número pasado como parámetro.

-diccionario.h: la piedra central de nuestro programa, ya que implementa nuestro diccionario de palabras. Se ha implementado mediante un multiset de string, pero aplicandole un functor, además tenemos dos datos miembro estáticos: modo y conjunto. Por ésto es un multiset, ya que al aplicarle el functor al insertar compara con él y sólo introduciría una palabra de cada longitud posible(si el modo fuera L) si fuera un set, con el multiset no ocurre. La idea de ésto es que al introducir las palabras se vayan ordenando de mayor a menor según longitud(si el modo es L) o puntuación(si el modo es P). Combinando ésto con la función preparar, que elimina del principio del diccionario las palabras imposibles de formar con el numero de letras dado, conseguimos que no sólo no tengamos que recorrer el diccionario entero, si no que por lo general recorremos una parte relativamente corta de él. Además, en vez de buscar las palabras permutando las letras aleatorias y buscando en el diccionario con cada permutación(que tendría que recorrer el diccionario tantas veces como permutaciones haya), se plantea de tal manera que, al estar ordenadas de esa manera, empezamos a recorrer el diccionario desde el principio y vamos comprobando que cada letra de la palabra del diccionario en la que estemos esté en nuestro vector de letras aletorias. En el momento en el que todas las letras de una palabra estén en nuestro vector ésta será la palabra con más puntuación posible en nuestro diccionario.

-Ejecución: la manera de ejecutar el programa se explica claramente cuando lo ejecutamos sin parámetros.
