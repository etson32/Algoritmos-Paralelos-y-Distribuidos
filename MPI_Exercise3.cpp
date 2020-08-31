/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 6
---------------------------------------------------------------------------------
Tarea1:
Escribir un programa paralelo con MPI para calcular la integral de la función:
f = 1/(x+1) + 1/(x^2+1)
Utilice el método de suma de trapecios bajo la curva.
*/
#include "stdafx.h"
#include <math.h>
#include "mpi.h" // Biblioteca de MPI
#include <cstdlib> // Incluido para el uso de atoi
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	int n, // Numero de iteraciones
	rank, // Identificador de proceso
	size; // Numero de procesos
	//double PI25DT = 3.141592653589793238462643;
	double myf, // Valor local de la funcion
	respuesta, // Valor globarl de la funcion
	h, // Aproximacion del area para el calculo de la funcion
	sum; // Acumulador para la suma del area de la funcion
	bool valor_por_parametros = true; // Comprueba si hay valores por parametros
	MPI_Init(&argc, &argv); // Inicializamos los procesos
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de procesos
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro proc.
										  // Solo el proceso 0 va a conocer el numero de iteraciones que vamos a
										  // ejecutar para la aproximacion de la funcion
	if (rank == 0) {
		//Cantidad de cortes que se va a tener para la aproximacion
		cout << "introduce la precision del calculo (n > 0): ";
		cin >> n;
	}
	// El proceso 0 reparte al resto de procesos el numero de iteraciones
	// que calcularemos para la aproximacion de la funcion
	MPI_Bcast(&n, // Puntero al dato que vamos a enviar
		1, // Numero de datos a los que apunta el puntero
		MPI_INT, // Tipo del dato a enviar
		0, // Identificacion del proceso que envia el dato
		MPI_COMM_WORLD);
	if (n <= 0) {
		MPI_Finalize();
		exit(0);
	}
	else {
		// Calculo de la funcion
		//El numerador es 1 por que no hay limites de integracion se considera 1-0 entonces  h=1/n
		h = 1.0 / (double)n;
		sum = 0.0;
		for (int i = rank + 1; i <= n; i += size) {
			double x = h * ((double)i - 0.5);
			sum += (1/x+1)+(1/(x*x +1));
		}
		myf = h * sum;
		// Todos los procesos ahora comparten su valor local de la funcion,
		// lo hacen reduciendo su valor local a un proceso
		// seleccionada a traves de una operacion aritmetica.
		MPI_Reduce(&myf, // Valor local de la funcion
			&respuesta, // Dato sobre el que vamos a reducir el resto
			1, // Numero de datos que vamos a reducir
			MPI_DOUBLE, // Tipo de dato que vamos a reducir
			MPI_SUM, // Operacion que aplicaremos
			0, // proceso que va a recibir el dato reducido
			MPI_COMM_WORLD);
		// Solo el proceso 0 imprime el mensaje, ya que es la unica que
		// conoce el valor de la funcion aproximado.
		if (rank == 0)
			cout << "El valor aproximado de la funcion f= (1/x+1) + (1/x*x +1) es: " << respuesta
			<< endl;
	}
	MPI_Finalize();
	return 0;
}
