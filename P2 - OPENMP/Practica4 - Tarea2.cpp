/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 4
---------------------------------------------------------------------------------
Tarea2
Escribir un programa paralelo con OpenMP para calcular la integral.
*/

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <omp.h>
using namespace std;
double empezar, terminar;
int main(int argc, char *argv[])
{
	int n,a,b;
	cout << "introduce el número de rectángulos (n > 0): ";
	cin >> n;
	cout << "introduce el limite inferior a (a > 0): ";
	cin >> a;
	cout << "introduce el limite superior b (b > 0): ";
	cin >> b;
	double h = (b-a )/ (double)n;
	double sum = 0.0;
	empezar = omp_get_wtime();
#pragma omp parallel for shared( sum )
	for (int i=1;i <= n; i++) 
	{
		double x = h * ((double)i - 0.5);
		sum += ((x*x*x)/3)+4*x;
	}
	sum = sum * h;
	terminar = omp_get_wtime();
	cout << "el valor aproximado es" << sum << endl;
	printf("El valor aproximado de la funcion es:  %g \n", sum);
	cout << "el tiempo de procesamiento fue: "	<< fixed << terminar - empezar << endl;
	getchar();
	getchar();
	return 0;
}
