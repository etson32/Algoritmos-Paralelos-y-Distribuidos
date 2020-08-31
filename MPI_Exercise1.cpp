/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
----------------------------------------------------------------------------------
PRACTICA 5
----------------------------------------------------------------------------------
TAREA1: 
Escribir un programa paralelo en MPI en el que cada proceso calcule la suma de los
elementos de un vector de tamaño N y muestre su resultado indicando el
número del proceso que ha hecho la suma.
*/
#include "stdafx.h"
#include <mpi.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
	int i, pid, npr, respuesta;
	int n = 10;
	respuesta = 0;
	int *vector = new int[n];
	MPI_Status info;
	//Llenar el vector con valores aleatorios
	for (int i = 0; i < n; i++)
	{
		vector[i] = (rand() % 4) + 1;
	}
	//Mostrar vector
	for (i = 0; i < n; i++)
	{
		printf("%d ", vector[i]);
		printf(" ");
	}
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npr);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	for (i = 0; i < n; i++)
	{
		//sumar los valores del vector
		respuesta = respuesta + vector[i];
		//En la ultima iteracion en cada hilo se debe mostrar el resultado y el hilo que trabajó
		if (i == n-1)
		{
			cout << "Proceso: " << pid << " Suma de los elementos del vector: " << respuesta << endl;
		}
    }
	MPI_Finalize();
	return 0;
}
