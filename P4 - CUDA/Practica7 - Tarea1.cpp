/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 7
---------------------------------------------------------------------------------
Tarea1
Escribir un programa CUDA para suma dos matrices.
*/
%%cu
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define T 2 // max threads x bloque
#define N 3 //Dimension de la matriz


__global__ void sumaMatrices(int *m1, int *m2, int *m3) {

/*printf("Soy el hilo %d en el bloque x= %d con dimension= %d \n",threadIdx.x,blockIdx.x,blockDim.x);*/
 int col = blockIdx.x * blockDim.x + threadIdx.x;
 int fil = blockIdx.y * blockDim.y + threadIdx.y;

 int indice = fil * N + col;
 
 if (col < N && fil < N) {
  // debido a que en los últimos bloques no se realizan todos los threads
  m3[indice] = m1[indice] + m2[indice];
  printf("Soy el hilo (x=%d,y=%d) en el bloque (x=%d,y=%d) con dimension (x=%d,y=%d) con indice %d y voy a sumar %d + %d = %d \n",threadIdx.x,threadIdx.y,blockIdx.x,blockIdx.y,blockDim.x,blockDim.y,indice,m1[indice],m2[indice],m3[indice]);
 }
}

int main(int argc, char** argv) {

 int m1[N][N];
 int m2[N][N];
 int m3[N][N];
 int i, j;
 int c = 0;

 /* inicializando variables con datos aleatorios*/
 for (i = 0; i < N; i++) {
  for (j = 0; j < N; j++) {
   m1[i][j] = rand()%(5);;
   m2[i][j] = rand()%(5);;
  }
 }
 /*Imprimimos la matriz1 */
printf("La matriz 1 de dimension %d x %d \n" ,N,N);
for (i = 0; i < N; i++)
{
for (j = 0; j < N; j++)
{
printf(" [%d,%d]=%d", i, j,m1[i][j]);
}
printf("\n");
}
printf("\n");
/*Imprimimos la matriz2 */
printf("La matriz 2 de dimension %d x %d \n" ,N,N);
for (i = 0; i < N; i++)
{
for (j = 0; j < N; j++)
{
printf(" [%d,%d]=%d", i, j,m2[i][j]);
}
printf("\n");
}

 int *dm1, *dm2, *dm3;

 //Creamos espacio para las matrices en la GPU
 cudaMalloc((void**) &dm1, N * N * sizeof(int));
 cudaMalloc((void**) &dm2, N * N * sizeof(int));
 cudaMalloc((void**) &dm3, N * N * sizeof(int));

 // copiando memoria a la GPGPU
 cudaMemcpy(dm1, m1, N * N * sizeof(int), cudaMemcpyHostToDevice);
 cudaMemcpy(dm2, m2, N * N * sizeof(int), cudaMemcpyHostToDevice);

 // cada bloque en dimensión x y y tendrá un tamaño de T Threads
 dim3 dimThreadsBloque(T, T);

 // Calculando el número de bloques en 1D
 float BFloat = (float) N / (float) T;
 int B = (int) ceil(BFloat);

 // El grid tendrá B número de bloques en x y y
 dim3 dimBloques(B, B);

 // Llamando a ejecutar el kernel
 sumaMatrices<<<dimBloques, dimThreadsBloque>>>(dm1, dm2, dm3);

 // copiando el resultado a la memoria Host
 cudaMemcpy(m3, dm3, N * N * sizeof(int), cudaMemcpyDeviceToHost);
 //cudaMemcpy(m2, dm2, N * N * sizeof(int), cudaMemcpyDeviceToHost);

 cudaFree(dm1);
 cudaFree(dm2);
 cudaFree(dm3);

 printf("\n");
 printf("Numero de bloques B = %d \n", B*B);
 printf("Dimension de bloques en (x=%d,y=%d) \n",dimBloques.x, dimBloques.y);
 printf("Dimension de los hilos por bloque en (x=%d,y=%d) \n",dimThreadsBloque.x, dimThreadsBloque.y); 
 printf("\n");
/*Imprimimos la matriz3 con el RESULTADO */
printf("La matriz suma de dimension %d x %d \n" ,N,N);
for (i = 0; i < N; i++)
{
for (j = 0; j < N; j++)
{
printf(" [%d,%d]=%d", i, j,m3[i][j]);
}
printf("\n");
}
 return 0;
}