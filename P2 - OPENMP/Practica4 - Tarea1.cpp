/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 4
---------------------------------------------------------------------------------
Tarea1
Diseñar un programa paralelo con OpenMP para calcular el resultado de multiplicar una matriz por
un vector.
*/

#include "stdafx.h"
#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	int i, j;
	srand(time(NULL));
	int n;
	cout << "ingrese el valor de n: ";
	cin >> n;
	int *vector = new int[n];
	//--crea las matrices n x n
	int **matriz_a = new int*[n];
	for (int i = 0; i < n; i++) {
		matriz_a[i] = new int[n];
	}
    //vector n*1

	int **matriz_c = new int*[n];
	for (int i = 0; i < n; i++) {
		matriz_c[i] = new int[n];
	}
	//--llena las matrices a con valores aleatorios
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			matriz_a[i][j] = (rand() % 4) + 1;
			
		}
	}
	//--llena el vector con valores aleatorios
	for (int i = 0; i < n; i++)
	{
		vector[i] = (rand() % 4) + 1;
	}
	/* muestra la matriz_a */
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", matriz_a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	/* muestra la matriz_b*/
	for (i = 0; i < n; i++)
	{
		printf("%d ", vector[i]);
		printf("\n");
	}
	printf("\n");
	/* realizar la multiplicación en paralelo */
#pragma omp parallel
	{
		int i, j, suma = 0;
#pragma omp for
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
			    suma += (matriz_a[i][j] * vector[j]);			
				matriz_c[i][j] = suma;
				suma = 0;
			}
		}
	}
	//-- muestra la matriz_c de resultados
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", matriz_c[i][j]);
		}
		printf("\n");
	}
	getchar();
	getchar();
	return 0;
}
