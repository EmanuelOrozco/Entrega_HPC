/*
Dada la función: f(x) = e^(-x^(2))

calcular la integral de esta función en el intervalo -1 hasta 1
utilizando los siguientes métodos de integración numérica, implementando tanto versiones secuenciales como paralelas de los algoritmos:

    Método de Simpson 1/3 de aplicación simple
    Método de Simpson 3/8 de aplicación simple
    Método de Simpson 1/3 de aplicación múltiple
    Método de Simpson 3/8 de aplicación múltiple

Mide los tiempos de ejecución de cada algoritmo en ambas versiones y calcula el speedup obtenido con la paralelización.

// Comando en bash para compilar el codigo: gcc -fopenmp -o Simpson Simpson.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Defino como variables globales los limites de integracion y los subintervalos (deben ser pares para el metodo de simpson 1/3)
#define A -1.0  
#define B 1.0   
#define N 1000000000

// Creo una funcion 'f' que retorna la funcion matematica que se evaluara respecto a 'X'
double f(double x) {
    return exp(-x * x);  // f(x) = e^(-x^2)
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Método de Simpson 1/3 en serie
double simpson_1_3(double a, double b, int n) {
    double h = (b - a) / n; // h es el ancho de cada subintervalo
    double sum_odd = 0.0, sum_even = 0.0; // Creo las variables para guardar las sumatorias de los valores indiviaduales
    int i;
    // Calculo impar
    for (i = 1; i <= n - 1; i += 2) {
        sum_odd += f(a + i * h); // Los valores impares los evaluo en la funcion y los guardo en sum_odd
    }
    // Calculo par
    for (i = 2; i <= n - 2; i += 2) {
        sum_even += f(a + i * h); // Los valores pares los evaluo en la funcion y los guardo en sum_even
    }
    // Uso la formula de Simpson
    // Los valores impares los multiplico por 4 y los pares por 2 y sumo los valores de los extremos
    double result = (h / 3) * (f(a) + 4 * sum_odd + 2 * sum_even + f(b));
    return result;
}

// Método de Simpson 1/3 en paralelo
double simpson_1_3_parallel(double a, double b, int n) {
    double h = (b - a) / n; 
    double sum_odd = 0.0, sum_even = 0.0; 
    int i;
    // Calculo impar
    #pragma omp parallel for reduction(+:sum_odd)
    for (i = 1; i <= n - 1; i += 2) {
        sum_odd += f(a + i * h);
    }
    // Calculo par
    #pragma omp parallel for reduction(+:sum_even)
    for (i = 2; i <= n - 2; i += 2) {
        sum_even += f(a + i * h);
    }
    // Uso la formula de Simpson
    double result = (h / 3) * (f(a) + 4 * sum_odd + 2 * sum_even + f(b));
    return result;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Método de Simpson 3/8 en serie
double simpson_3_8(double a, double b, int n) {
    double h = (b - a) / n; // h es el ancho de cada subintervalo
    double sum_3m = 0.0, sum_rest = 0.0; // Creo las variables para guardar las sumatorias de los valores indiviaduales
    int i;
    // Calculo multiplos de 3
    for (i = 3; i < n; i += 3) {
        sum_3m += f(a + i * h);
    }
    // Calculo los demas
    for (i = 1; i < n - 1; i++) {
        if (i % 3 == 0) { // Si el indice es multiplo de 3 lo salto
            continue;
        }
        sum_rest += f(a + i * h);
    }
    // Uso la formula de Simpson 3/8
    double result = (3 * h / 8) * (f(a) + 3 * sum_3m + 3 * sum_rest + f(b));
    return result;
}

// Método de Simpson 3/8 en paralelo
double simpson_3_8_parallel(double a, double b, int n) {
    double h = (b - a) / n; // h es el ancho de cada subintervalo
    double sum_3m = 0.0, sum_rest = 0.0; // Creo las variables para guardar las sumatorias de los valores indiviaduales
    int i;
    // Calculo multiplos de 3
    # pragma omp parallel for reduction(+:sum_3m)
    for (i = 3; i < n; i += 3) {
        sum_3m += f(a + i * h);
    }
    // Calculo los demas
    # pragma omp parallel for reduction(+:sum_rest)
    for (i = 1; i < n - 1; i++) {
        if (i % 3 == 0) { 
            continue;
        }
        sum_rest += f(a + i * h);
    }
    // Uso la formula de Simpson 3/8
    double result = (3 * h / 8) * (f(a) + 3 * sum_3m + 3 * sum_rest + f(b));
    return result;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

int main() {
    double start_time_1, start_time_2, start_time_3, start_time_4;
    double end_time_1, end_time_2, end_time_3, end_time_4;

    // En serie
    start_time_1 = omp_get_wtime();
    double result_1_3 = simpson_1_3(A, B, N);
    end_time_1 = omp_get_wtime();
    printf("Simpson 1/3 en serie: %.15f\n", result_1_3);
    printf("Tiempo secuencial: %.6f segundos\n", end_time_1 - start_time_1);

    start_time_2 = omp_get_wtime();
    double result_3_8 = simpson_3_8(A, B, N);
    end_time_2 = omp_get_wtime();
    printf("Simpson 3/8 en serie: %.15f\n", result_3_8);
    printf("Tiempo secuencial: %.6f segundos\n", end_time_2 - start_time_2);

    // En paralelo
    start_time_3 = omp_get_wtime();
    double result_1_3_parallel = simpson_1_3_parallel(A, B, N);
    end_time_3 = omp_get_wtime();
    printf("Simpson 1/3 paralelo: %.15f\n", result_1_3_parallel);
    printf("Tiempo paralelo: %.6f segundos\n", end_time_3 - start_time_3);

    start_time_4 = omp_get_wtime();
    double result_3_8_parallel = simpson_3_8_parallel(A, B, N);
    end_time_4 = omp_get_wtime();
    printf("Simpson 3/8 paralelo: %.15f\n", result_3_8_parallel);
    printf("Tiempo paralelo: %.6f segundos\n", end_time_4 - start_time_4);

    // Calculo el Speedup
    double speedup_1_3 = (end_time_1 - start_time_1) / (end_time_3 - start_time_3);  // reemplazar con tiempos reales
    double speedup_3_8 = (end_time_2 - start_time_2) / (end_time_4 - start_time_4);  // reemplazar con tiempos reales

    printf("Speedup Simpson 1/3: %.2f\n", speedup_1_3);
    printf("Speedup Simpson 3/8: %.2f\n", speedup_3_8);

    return 0;
}
