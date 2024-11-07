/*
Ejercicio:
Optimizar un programa paralelo que realiza operaciones sobre grandes arreglos utilizando 
punteros y comparar el tiempo de ejecución con una implementación sin punteros.

Instrucciones:
    Implementar dos versiones de un programa que manipule un array grande: una versión usando paso por valor y otra usando punteros.
    Medir y comparar los tiempos de ejecución en ambos enfoques.
    Analizar los resultados y explicar cómo el uso de punteros mejora el rendimiento.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Función con paso por valor (se crea una copia)
void procesoPorValor(int array[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        array[i] += i;
    }
}

// Función con paso por referencia (se usa punteros)
void procesoPorReferencia(int *array, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        array[i] += i;
    }
}

int main() {
    int n = 10000000;  // Tamaño del arreglo (10 millones)
    
    // Reservar memoria para los arreglos
    int *array1 = (int *)malloc(n * sizeof(int));
    int *array2 = (int *)malloc(n * sizeof(int));
    
    // Corroboro que esten los arrays, aunque ya estan por defecto
    if (!array1 || !array2) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Inicializo los arreglos en 0
    for (int i = 0; i < n; i++) {
        array1[i] = array2[i] = 0;
    }

    // Mido el tiempo de paso por valor (copia)
    clock_t start = clock();
    procesoPorValor(array1, n);
    clock_t end = clock();
    double tiempoValor = (double)(end - start) / CLOCKS_PER_SEC;

    // Mido el tiempo de paso por referencia (punteros)
    start = clock();
    procesoPorReferencia(array2, n);
    end = clock();
    double tiempoReferencia = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tiempo con paso por valor (copia): %.6f segundos\n", tiempoValor);
    printf("Tiempo con paso por referencia (puntero): %.6f segundos\n", tiempoReferencia);

    // Libero la memoria
    free(array1);
    free(array2);

    return 0;
}
