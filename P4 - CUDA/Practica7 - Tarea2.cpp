/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 7
---------------------------------------------------------------------------------
Tarea2
Escribir un programa CUDA para multiplicar una matriz por un vector.
*/
%%cu
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define T 1 // max threads x bloque
#define N 3 //Dimension de la matriz


__global__ void sumaMatrices(int *m1, int *m2, int *m3) {

/*printf("Soy el hilo %d en el bloque x= %d con dimension= %d \n",threadIdx.x,blockIdx.x,blockDim.x);*/
 int col = blockIdx.x * blockDim.x + threadIdx.x;
 int fil = blockIdx.y * blockDim.y + threadIdx.y;
 int indice = fil * N + col;
 int cont=indice*N;
 int suma=0;
 int k;
 if (indice < N) {
  // debido a que en los últimos bloques no se realizan todos los threads
  for(k=0;k<N;k++)
  {
      printf("Vamos a operar: %d + ( %d * %d ) = %d  \n",suma,m1[cont+k],m2[k],suma+ m1[cont+k]*m2[k]);
      suma = suma + (m1[cont+k] * m2[k]);    
      printf("Suma[ %d ] es: %d \n",k,suma);
  }
  m3[indice]=suma;
  printf("Suma final es: %d \n",suma);
 }
}

int main(int argc, char** argv) {

 int m1[N][N];
 int m2[N];
 int m3[N];
 int i, j;
 int c = 0;

 /* inicializando variables con datos aleatorios*/
 for (i = 0; i < N; i++) {
      m2[i] = rand()%(9);
  for (j = 0; j < N; j++) {
   m1[i][j] = rand()%(9);
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
printf("El vector de dimension %d \n" ,N);
for (i = 0; i < N; i++)
{
printf(" [%d]=%d", i, m2[i]);
printf("\n");
}

 int *dm1, *dm2, *dm3;

 //Creamos espacio para las matrices en la GPU
 cudaMalloc((void**) &dm1, N * N * sizeof(int));
 cudaMalloc((void**) &dm2, N * sizeof(int));
 cudaMalloc((void**) &dm3, N * sizeof(int));

 // copiando memoria a la GPGPU
 cudaMemcpy(dm1, m1, N * N * sizeof(int), cudaMemcpyHostToDevice);
 cudaMemcpy(dm2, m2, N * sizeof(int), cudaMemcpyHostToDevice);

 // cada bloque en dimensión x y y tendrá un tamaño de T Threads

dim3 dimGrid(1, 1);
dim3 dimBlock(N, N);

 // Llamando a ejecutar el kernel
 sumaMatrices<<<dimGrid, dimBlock>>>(dm1, dm2, dm3);

 // copiando el resultado a la memoria Host
 cudaMemcpy(m3, dm3, N * sizeof(int), cudaMemcpyDeviceToHost);
 //cudaMemcpy(m2, dm2, N * sizeof(int), cudaMemcpyDeviceToHost);

 cudaFree(dm1);
 cudaFree(dm2);
 cudaFree(dm3);

 printf("\n");
/*printf("Numero de bloques B = %d \n", blockDim.x*blockDim.y);*/
/* printf("Dimension de bloques en (x=%d,y=%d) \n",blockDim.x, blockDim.y);*/
/* printf("Dimension de los hilos por bloque en (x=%d,y=%d) \n",dimThreadsBloque.x, dimThreadsBloque.y); */
 printf("\n");
/*Imprimimos el vector con el RESULTADO */
printf("La matriz resultante (Matriz * Vector) de dimension %d x %d \n" ,N,N);
for (i = 0; i < N; i++)
{
printf(" [%d]=%d",i ,m3[i]);
printf("\n");
}
 return 0;
}