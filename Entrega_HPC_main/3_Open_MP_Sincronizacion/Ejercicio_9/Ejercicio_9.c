/*
Ejercicio 2: 
Paralelización del cálculo de la norma de un vector - 

Implementar paralelismo en el cálculo de la norma de un vector en un espacio N-dimensional, aplicando la directiva #pragma omp simd para optimizar el cálculo.

Escribe un programa en C que:
   Genere un vector con N componentes aleatorias.
    Calcule la norma utilizando paralelismo SIMD para los cuadrados de los elementos y sincronización para la suma total.

    Pseudocódigo
    - Inicializar un vector con números aleatorios.
    - Paralelizar el cálculo de la suma de los cuadrados utilizando `#pragma omp simd`.
    - Sincronizar los resultados y calcular la raíz cuadrada.

Desafío adicional: 
Aumentar el tamaño del vector a 10 millones de elementos y observar el impacto en el tiempo de ejecución antes y después de la vectorización.

// Comando en bash para compilar el codigo: gcc -fopenmp -o Ejercicio_9 Ejercicio_9.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

// Creo un vector con N numeros aleatorios entre 0 y 99
void generar_vector(double *vector, int N) {
    for (int i = 0; i < N; i++) {
        vector[i] = rand() % 100;  
    }
}

// Funcion para calcular la norma del vector
double calcular_norma(double *vector, int N) {
    double suma = 0.0;

    // Calculo la suma de los cuadrados con paralelismo (simd)
    #pragma omp parallel for simd reduction(+:suma)
    for (int i = 0; i < N; i++) {
        suma += vector[i] * vector[i];  
    }

    return sqrt(suma); 
}

int main() {
    int N = 10000000;  
    
    // Reservo memoria para el vector
    double *vector = (double *)malloc(N * sizeof(double));
    if (vector == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Genero el vector de numeros aleatorios
    generar_vector(vector, N);

    // Mido el tiempo
    double inicio = omp_get_wtime();
    
    // Calculo la norma para el vector
    double norma = calcular_norma(vector, N);

    double fin = omp_get_wtime();
    
    printf("La norma del vector es: %.6f\n", norma);
    printf("Tiempo de ejecución: %.6f segundos\n", fin - inicio);

    // Libero la memoria
    free(vector);

    return 0;
}
