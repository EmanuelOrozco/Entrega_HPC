/*
Ejercicio 3: 
Paralelización de un Bucle for - 

Escribe un programa que calcule la suma de los números enteros del 1 al 100 utilizando un bucle for paralelo con OpenMP. 
Cada hilo debe calcular la suma de una parte del rango y al final combinar los resultados utilizando la cláusula reduction.
*/

#include <stdio.h>
#include <omp.h>

int main() {
    // Creo una variable para guardar la suma
    int sum = 0;

    // Inicio la paralelizacion del bucle for
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= 100; i++) {
        sum += i; 
    }

    // Imprimo el total
    printf("La suma de los números del 1 al 100 es: %d\n", sum);

    return 0;
}
