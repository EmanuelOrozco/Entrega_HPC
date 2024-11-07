/*
Ejercicio 1: 
Suma de series paralelas con condiciones de carrera - 

Dado un vector de números aleatorios, paraleliza el cálculo de la suma de sus elementos utilizando OpenMP. 
Inicialmente, introduce una condición de carrera para que los estudiantes vean el problema. 
Luego, deben solucionarlo utilizando una sección crítica o una directiva atómica.

    pseudocode
    - Generar un vector aleatorio de 1,000,000 números.
    - Calcular la suma de los elementos en paralelo.
    - Corregir la condición de carrera usando `#pragma omp critical` o `#pragma omp atomic`.

Desafío adicional: 
Extiende el programa para que también calcule la suma cuadrada (sumar el cuadrado de cada número del vector) en paralelo, garantizando la sincronización adecuada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Genero un vector de numeros aleatorios entre 0 y 99
void generar_vector(int *vector, int tamano) {
    for (int i = 0; i < tamano; i++) {
        vector[i] = rand() % 100;  
    }
}

// Sumo los elemntos del vector con condicion de carrera
void suma_condicion_carrera(int *vector, int tamano, int *suma) {
    #pragma omp parallel for
    for (int i = 0; i < tamano; i++) {
        *suma += vector[i]; 
    }
}

// Sumo los elementos del vector con sincronizacion, evitando la sincronizacion de carrera
void suma_con_sincronizacion(int *vector, int tamano, int *suma) {
    #pragma omp parallel for
    for (int i = 0; i < tamano; i++) {
        #pragma omp atomic // con el 'atomic' solo un hilo ingresa a la vez
        *suma += vector[i];  
    }
}

// Calculo la suma cuadrada
void suma_cuadrados(int *vector, int tamano, int *suma_cuadrados_resultante) {
    #pragma omp parallel for
    for (int i = 0; i < tamano; i++) {
        #pragma omp atomic
        *suma_cuadrados_resultante += vector[i] * vector[i]; 
    }
}

int main() {
    int tamano_vector = 1000000; 
    
    // Reservo la memoria para el vector
    int *vector = (int *)malloc(tamano_vector * sizeof(int));
    int suma = 0;
    int suma_cuadrados_resultante = 0;

    if (vector == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // genero el vector con los numeros aleatorios
    generar_vector(vector, tamano_vector);

    // Calculo la suma con condicion de carrera
    double inicio = omp_get_wtime();
    suma_condicion_carrera(vector, tamano_vector, &suma);
    double fin = omp_get_wtime();
    printf("Suma con condición de carrera: %d\n", suma);
    printf("Tiempo con condición de carrera: %.6f segundos\n", fin - inicio);

    // Calculo la suma sin condicion de carrera
    suma = 0;  // Reiniciar la suma
    inicio = omp_get_wtime();
    suma_con_sincronizacion(vector, tamano_vector, &suma);
    fin = omp_get_wtime();
    printf("Suma con sincronización (atomic): %d\n", suma);
    printf("Tiempo con sincronización (atomic): %.6f segundos\n", fin - inicio);

    // Calculo la suma de los cuadrados
    suma_cuadrados_resultante = 0;  
    inicio = omp_get_wtime();
    suma_cuadrados(vector, tamano_vector, &suma_cuadrados_resultante);
    fin = omp_get_wtime();
    printf("Suma de los cuadrados con sincronización (atomic): %d\n", suma_cuadrados_resultante);
    printf("Tiempo para la suma de cuadrados: %.6f segundos\n", fin - inicio);

    // Libero la memoria
    free(vector);

    return 0;
}
