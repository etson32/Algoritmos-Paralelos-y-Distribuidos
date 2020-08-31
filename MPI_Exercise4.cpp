/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 6
---------------------------------------------------------------------------------
TAREA2:
Escribir un programa paralelo para que en una ejecución con cuatro procesos,
P0 reparte datos del vector B (de 16 enteros) de la siguiente manera: a P2: B[3],
B[4], B[5]; a P1: B[7], B[8]; a P0: B[10]; y a P3: B[12], B[13], B[14], B[15]. Tras
ello, cada proceso suma 100 a los elementos recibidos, y, finalmente, se
recopilan los datos finales en P0, en las mismas posiciones iniciales del vector B.
*/
#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include "mpi.h"
int main(int argc, char **argv)
{
	//Inicializamos variables
	int p, np ,i;	
	int B[16], C[16], tam[4], desp[4];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	/* Inicializaciones en todos los procesos */
	for (i = 0; i<16; i++) 
	{ 
		//A B le pasamos los punteros como dato
		B[i] = i;
		//A C lo inicializamos con 0
		C[i] = 0; 
	}
	if (p == 0) {
		//En el proceso 0 mostramos el vector generado 
		printf("\n Vector Inicial B en P0:= %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d\n", B[0], B[1], B[2], B[3], B[4], B[5], B[6], B[7], B[8], B[9], B[10], B[11], B[12], B[13], B[14], B[15]);
	}
	/* Reparto de B (16 elementos) desde P0 en 4 trozos: 1, 2, 3, 4 elementos */
	/* vector de tamainos de los trozos */
	tam[0] = 1; tam[1] = 2; tam[2] = 3; tam[3] = 4;
	/* vector de desplazamientos desde el origen a cada trozo */
	desp[0] = 10; desp[1] = 7; desp[2] = 3; desp[3] = 12;
	//Operacion para repartir datos a los diferentes procesos (en tamaños diferentes)
	MPI_Scatterv(&B[0], tam, desp, MPI_INT, &C[0], tam[p], MPI_INT, 0, MPI_COMM_WORLD);
	//Sumar 100 a los datos recibidos
	for (int i = 0; i < 16; i++)
	{
		if(C[i]!=0)
		C[i] += 100;
	}
	//Verificar si los datos enviados por el proceso 0 fueron sumados por 100
	printf("\n Datos enviados al proceso P%d C =%2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d\n", p, C[0], C[1], C[2], C[3], C[4], C[5], C[6], C[7], C[8], C[9], C[10], C[11], C[12], C[13], C[14], C[15]);
	//Operacion para recibir los datos que fueron enviados a los anteriores procesos
	MPI_Gatherv(&C[0], tam[p], MPI_INT, &B[0],tam, desp,MPI_INT, 0, MPI_COMM_WORLD);
	//El proceso 0 Imprime el vector B actualizado
	if (p == 0)
	{
		printf("\n Vector B Actualizado en P0:= %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d %2d\n", B[0], B[1], B[2], B[3], B[4], B[5], B[6], B[7], B[8], B[9], B[10], B[11], B[12], B[13], B[14], B[15]);
	}
	MPI_Finalize();
}
