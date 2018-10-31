Informe tarea 2 - Memoria Virtual (Paginación bajo demanda)

En este informe se explicara el funcionamiento para la tarea 2 de Sistemas Operativos y Redes. Para esta tarea se pidio implementar 3 algoritmos para cubrir la paginacion bajo demanda (FIFO, Rand y uno creado para esta tarea (custom)). Para terminos practicos, fue entregado todo el "esqueleto" del codigo, el cual contenia todos los archivos necesarios para hacer swapping entre la tabla de pagina virtual y el disco virtual y el manejo de algunos inputs, lo unico que falto por implementar fueron los algoritmos dichos anteriormente.

En el enunciado se explica el funcionamiento completo y en detalle de la paginacion, pero basicamente funciona en que se tiene una memoria fisica vacia, a la cual la memoria virtual consulta por una pagina, al no estar la pagina se lee el disco y se escribe dicha pagina dentro de la memoria fisica. Cuando existen menos marcos que paginas ocurre una "falta de pagina" donde se ocupa una funcion para limpiar un marco y poder escribir la pagina dentro de el.

Se comenzara explicando el funcionamiento de los distintos algoritmos que manejan las faltas de pagina en la tarea.

FIFO:
Este algoritmo tiene la funcion de eliminar el primer elemento que entro, en este caso seria eliminar la primera pagina en ocupar un marco para hacerle "espacio" a la siguiente pagina. Luego la segunda pagina pasa a ser eliminada al haber otra falta de pagina y asi sucesivamente.

Rand:
Este algoritmo elige un marco al azar, si hay una pagina en dicho marco, esta es escrita en el disco y se cargara desde el disco la pagina nueva en dicho marco.

Custom:
Este algoritmo consta de la mezcla de los otros dos con una variable "bit" que va cambiando entre 0 y 1 cada vez que se utiliza uno de los 2 algoritmos.

Al iniciar el programa se encontrara la memoria de tamaño igual a la cantidad de marcos y vacia, todo se encontrara dentro de el disco y dependiendo de la cantidad de paginas ocurriran las escrituras al disco (si la cantidad de paginas es menor o igual a la de marcos no habra escritura al disco, pero si es mayor dependera del algoritmo usado la cantidad de lecturas al disco). Basicamente lo que hacen los algoritmos es definir el marco el cual se vera si esta vacio o ocupado para aplicar las distintas funciones incorporada en los distintos archivos entregados.

HIPOTESIS DE PRUEBAS

Se haran pruebas de los 3 algoritmos implementados y se compararan entre ellos.
Se fijara la cantidad de marcos a 100 y el numero de paginas variara entre 2 y 100.

Viendo el funcionamiento, es de esperarse que el algoritmo "fifo" tenga la menor cantidad de escrituras al disco debido a que se van llenando inicialmente los espacios vacios por lo cual siempre va a tener una cantidad de escrituras al disco de (numero de paginas - numero de marcos) a excepcion de que el numero de paginas sea menor o igual al numero de marcos. 

Los otros 2 al tener random incorporado puede leer un marco ocupado cuando puede haber otro desocupado, escribiendo al disco de manera innecesaria, aca no importaria la cantidad de paginas y la cantidad de marcos






Iñaki Errázuriz

PD: La invocacion de el programa es de el estilo "$./virtmem 100 10 rand sort" como sale en el enucnciado, ante la duda lo consulte con Claudio y me dijo que no hay problema.

PD2: Cabe destacar que en el enunciado se pidio usar lrand48(), lo cual genera numeros aleatorios, pero genera siempre los mismos numeros aleatorios si se repiten las condiciones.