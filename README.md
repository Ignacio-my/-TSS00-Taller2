# TSSOO-Taller2
# TSSOO-taller01
autor: Ignacio Miranda

Correo Institucional: ignacio.miranda@alumnos.uv.cl

El diseño de la solucion consiste en 2 funciones, 

Funciones

LLenado(): calcula el tiempo del promedio de la simulacion y su memoria usada, el conjunto de archivos que ocupa es executionSummary y el archivo en el cual muestra los datos es llamado metrics.txt

SumaParalela(): calcula el tiempo promedio del uso de los telefonos moviles, el conjunto de archivos que ocupa es usePhone y el archivo en el cual muestra los datos es llamado usePhone-stats.txt

Conjunto de variables dentro de cada funcion

OUTFILE: variable en la cual se escribiran los datos que pide cada problema

archivoUsoEjecucion: variable en la cual se abren todos los archivos que tiene los datos necesarios para la solucion del problema

tmpFile: archivo temporal donde se dejan los datos especificos para calcular la solucion del problema estos datos se tomaron de los archivos de la variable archivoUsoEjecucion 

calculo: variable que se ocupa de calcular los datos del archivo tmpFile estos seran el total, promedio, minimo y maximo
  
