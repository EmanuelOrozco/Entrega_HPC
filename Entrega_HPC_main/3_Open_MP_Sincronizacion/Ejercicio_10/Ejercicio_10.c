/*
Ejercicio 3: 
Movimiento rectilíneo uniformemente acelerado (MRUA) - 
Modela el movimiento de un objeto bajo movimiento rectilíneo uniformemente acelerado (MRUA), 
donde el objeto parte de una posición inicial con una velocidad inicial, y se actualizan la posición y la velocidad en función de la aceleración

Utiliza OpenMP para calcular las posiciones y velocidades en varios puntos de tiempo de forma paralela, 
pero respetando las dependencias (cada posición futura depende de la posición anterior).

    Pseudocódigo
    - Inicializar valores de velocidad y posición.
    - Crear tareas para calcular posición y velocidad en diferentes tiempos t.
    - Utilizar dependencias para asegurar que cada tarea respete los cálculos previos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_TIEMPO 10  
#define NUM_PUNTOS 100 
#define V0 0           // Velocidad 
#define X0 0           // Posición 
#define A 2            // Aceleración 

// Creo una estructura llamada Estado donde guardo la informacion para cada punto
typedef struct {
    double tiempo;
    double posicion;
    double velocidad;
} Estado;

int main() {
    double delta_t = MAX_TIEMPO / (double)(NUM_PUNTOS - 1); // Encuentro el intervalo de tiempo
    Estado *estados = (Estado*)malloc(NUM_PUNTOS * sizeof(Estado));

    // Inicio los valores iniciales
    estados[0].tiempo = 0.0;
    estados[0].posicion = X0;
    estados[0].velocidad = V0;

    // Paralelizo respetando las dependencias
    #pragma omp parallel for schedule(dynamic) shared(estados)
    for (int i = 1; i < NUM_PUNTOS; i++) {

        // Un hilo a la vaz
        #pragma omp critical
        {
            estados[i].tiempo = estados[i-1].tiempo + delta_t;
            estados[i].velocidad = V0 + A * estados[i].tiempo;
            estados[i].posicion = X0 + V0 * estados[i].tiempo + 0.5 * A * estados[i].tiempo * estados[i].tiempo;
        }
    }

    printf("Tiempo(s)\tPosición(m)\tVelocidad(m/s)\n");
    for (int i = 0; i < NUM_PUNTOS; i++) {
        printf("%.2f\t%.2f\t%.2f\n", estados[i].tiempo, estados[i].posicion, estados[i].velocidad);
    }

    free(estados);
    return 0;
}
