/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 2
---------------------------------------------------------------------------------
Tarea1
Se requiere realizar la suma de dos arreglos unidimensionales de 10 elementos de
forma paralela utilizando solo dos hilos.Para ello se utilizará un paralelismo de datos
o descomposición de dominio, es decir, cada hilo trabajará con diferentes elementos
de los arreglos a sumar, pero ambos utilizarán el mismo algoritmo para realizar la
suma.
*/

#include <stdafx.h>
#include <iostream>
#include <omp.h>
#include <Windows.h>
using namespace std;

int main()
{
	//Declaramos las variables compartidas
	//Variables de identificacion de hilo
	int tid;
	//Primer vector
	int vector1[] = {1,2,3,4,5,6,7,8,9,10};
	//Segundo vector
	int vector2[] = {11,12,13,14,15,16,17,18,19,20};
	//Variable auxiliar donde se guardara la suma de los vectores
	int vectorsuma[10];
	//Region Paralela
	#pragma omp parallel private(tid)
	{
		//Obtenemos el id del hilo
		tid = omp_get_thread_num();
		//Si el hilo es cero se le asignara una tarea
		if (tid == 0)
		{
			//Suma de los dos vectores en el vector auxiliar con posiciones desde 0 hasta 4
			for (int i=0;i<5;i++)
			vectorsuma[i]= vector1[i] + vector2[i];
		}
		//Si el hilo es uno se le asignara una tarea
		if (tid == 1)
		{
			//Suma de los dos vectores en el vector auxiliar con posiciones desde 5 hasta 9
			for (int i = 5; i<10; i++)
			vectorsuma[i] = vector1[i] + vector2[i];
		}
	}
	//Imprimir suma de los elementos de los vectores
	for (int i = 0; i < 10; i++)
	{
		std::cout << " " << vectorsuma[i] << std::endl;
	}
	getchar();
	return 0;
}