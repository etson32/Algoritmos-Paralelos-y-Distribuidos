/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 5
---------------------------------------------------------------------------------
TAREA2: 
Escribir un programa paralelo para que el proceso 0 envíe dos números reales
al proceso 1 y éste devuelva el resultado de la suma al proceso 0 que lo
imprimirá.
*/
#include "stdafx.h"
#include <stdio.h>
#include "mpi.h"
#include <iostream>
int main(int argc, char **argv)
{
	int rank, size; 
	//Declaramos un vector de dos numeros reales
	double value[2]; 
	MPI_Status status;
	double suma = 0.0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//El proceso maestro envia dos elementos dentro de un vector al proceso 1
	if (rank == 0)
	{	//Generamos 2 valores aleatorios
		for (int i = 0; i < 2; i++)
		{
			value[i] = rand()%100 * 0.1;

		}
		printf("Soy el proceso %d y envio el valor %g y %g al proceso %d \n",rank, value[0], value[1], rank + 1);
		MPI_Send(&value, 2, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
	}
	else
	{
		//El proceso 1 recibe lo que envio el proceso maestro
		if (rank == 1)
		{
			MPI_Recv(&value, 2, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &status);
			printf("Soy el proceso %d y recibi el valor %g y %g del proceso %d \n", rank, value[0], value[1], rank - 1);
			//Se calcula la suma de los dos valores reales
			for (int i = 0; i < 2; i++)
			{
				suma = suma + value[i];
			}

			//Se envia el resultado al proceso maestro
			MPI_Send(&suma, 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD);
			printf("Soy el proceso %d y estoy enviando la suma al proceso %d \n", rank, rank - 1);
		}
	}
	//El proceso maestro recibira lo que envio el proceso 1
	if (rank == 0)
	{
		//El proceso maestro recibe un valor del proceso 1 y luego lo imprime
		MPI_Recv(&suma, 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD, &status);
		printf("Soy el proceso %d y recibi el valor suma de %g del proceso %d \n", rank, suma, rank + 1);
	}
	MPI_Finalize();
	return 0;
}

