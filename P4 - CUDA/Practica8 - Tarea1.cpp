/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 8
---------------------------------------------------------------------------------
Tarea1
Considerar un array a = (a0, a1, . . . ,an-1) de números enteros. Construir un kernel
invierte_array que reciba a y devuelva b = (an-1; an-2,. . . , a1, a0).
¿Cuál es el máximo tamaño que puede tener el vector? ¿Por qué?
*/
%%cu
#include <stdio.h>
#include <stdlib.h>
#define N 1024
// CUDA constants
__constant__ float dev_A[N];
// declaracion de funciones
// GLOBAL: funcion llamada desde el host y ejecutada en el device (kernel)
__global__ void invierte_array(float* dev_B)
{ // kernel lanzado con un solo bloque y NxN hilos
int columna = threadIdx.x;
int pos = (N-1)-columna;
// cada hilo coloca un elemento del vector final
dev_B[pos] = dev_A[columna];
}
// MAIN: rutina principal ejecutada en el host
int main(int argc, char** argv) {
// declaraciones
float* hst_A, * hst_B;
float* dev_B;
// reserva en el host

hst_A = (float*)malloc(N * sizeof(float));
hst_B = (float*)malloc(N * sizeof(float));
// reserva en el device
cudaMalloc((void**)&dev_B, N * sizeof(float));
// inicializacion
for (int i = 0; i < N ; i++)
{
hst_A[i] = (float)i;
}
// copia de datos
cudaMemcpyToSymbol(dev_A, hst_A, N *  sizeof(float));
// dimensiones del kernel
dim3 Nbloques(1);
dim3 hilosB(N, 1);
// llamada al kernel bidimensional de NxN hilos
invierte_array <<< Nbloques, hilosB >>> (dev_B);
// recogida de datos
cudaMemcpy(hst_B, dev_B, N *  sizeof(float),
cudaMemcpyDeviceToHost);
// impresion de resultados printf("Resultado:\n"); printf("ORIGINAL:\n");
printf("\n Vector Original:\n");
for (int i = 0; i < N; i++) {
printf("%2.0f ", hst_A[i]);
}
printf("\n Vector Invertido:\n");
for (int i = 0; i < N; i++) {
printf("%2.0f ", hst_B[i]);
}
}