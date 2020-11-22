/*Universidad Nacional San Antonio Abad del Cusco
Algoritmos Paralelos y Distribuidos 2019-II
Ingenieria Informatica y de Sistemas
Rojas Cahuana Etson Ronaldao
---------------------------------------------------------------------------------
PRACTICA 1
---------------------------------------------------------------------------------
Tarea1
Escribir un programa para que el cuerpo del hilo calcule la suma de los elementos de
un vector de enteros el cual es pasado como parámetro. Cada hilo en ejecución
devuelve la suma del vector al programa principal el cuál calcula la suma total y
muestra el resultado. 
*/
#include <iostream>
#include <vector>
#include <thread>

using namespace std;
void f(std::vector <int> v)
{
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}
int main()
{
	int s1;
	std::vector<int> pares = { 10, 20, 40, 60, 80 };
	std::vector<int> impares = { 1, 3, 5, 7, 9 };
	/* Lanza dos threads t1 y t2 */
	std::thread t1(f, pares);
	std::thread t2(f, impares);
	/* Espera que finalicen */
	t1.join();
	t2.join();
	getchar();
}