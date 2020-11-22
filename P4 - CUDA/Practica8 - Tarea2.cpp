/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 8
---------------------------------------------------------------------------------
Tarea2
Escribir un programa paralelo para calcular el valor de la siguiente integral.
*/
%%cu
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>
#define N 512
#define E 2.71828182845
// kernel
__global__ void evaluar(float* suma)
{
// Reserva de espacio en la zona de memoria compartida
__shared__ float temporal[N];
// Indice local de cada hilo -> kernel con un solo bloque
int myID = threadIdx.x;
// Generamos en 'temporal' el valor de la serie
int D = myID+1;
float x= -(D*D)/(N*N);
float temp = powf(E,x)/N;
temporal[myID] = temp;
__syncthreads();
//Reduccion paralela
int salto = N / 2;
// Realizamos log2(N) iteraciones
while (salto)
{
// Solo trabajan la mitad de los hilos
if (myID < salto)
{
temporal[myID] = temporal[myID] + temporal[myID + salto];
}
__syncthreads();
salto = salto / 2;
}
// El hilo no.'0' escribe el resultado final en la memoria global
if (myID == 0)
{
suma[0] = temporal[myID];
}
}
int main()
{
// declaraciones
float* suma;
float* dev_suma;
// reserva en el host
suma = (float*)malloc(sizeof(float));
// reserva en el device
cudaMalloc((void**)&dev_suma, sizeof(float));
// lanzamiento del kernel
printf("Calcular el valor de la integral en base %d términos\n", N);
evaluar << < 1, N >> > (dev_suma);
// recogida de datos desde el device
cudaMemcpy(suma, dev_suma, sizeof(float), cudaMemcpyDeviceToHost);
// calcular el valor de final
float ValorFinal = sqrt(suma[0] * 0.557);
// impresion de resultados
printf("Resultado: %.10f\n", ValorFinal);
// liberamos memoria en el device
cudaFree(suma);
// salida
printf("\npulsa INTRO para finalizar...");
fflush(stdin);
char tecla = getchar();
return 0;
}