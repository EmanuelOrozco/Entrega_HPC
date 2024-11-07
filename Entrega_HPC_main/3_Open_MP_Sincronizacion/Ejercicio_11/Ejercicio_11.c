/*
Ejercicio 5: 
Cálculo de Pi usando el método Monte Carlo - 

Este método consiste en generar puntos aleatorios dentro de un cuadrado y contar cuántos caen dentro de un círculo inscrito. 
La razón entre los puntos dentro del círculo y el total de puntos generados aproxima el valor de pi.

Escribe un programa que:
    Genere puntos aleatorios.
    Determine cuántos de ellos caen dentro del círculo.
    Calcule pi en paralelo

    Pseudocódigo
    - Generar puntos aleatorios en el plano (x, y).
    - Contar los puntos que caen dentro del círculo (x^2 + y^2 <= 1).
    - Paralelizar el proceso de conteo utilizando `#pragma omp parallel for`.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_PUNTOS 1000000

int main() {
    // Creo la variable apra guardar los puntos
    int puntos_dentro_del_circulo = 0;

    // Paralelizo con reduction
    #pragma omp parallel for reduction(+:puntos_dentro_del_circulo)
    for (int i = 0; i < NUM_PUNTOS; i++) {

        // Genero el punto en un intervalo de maximo 1
        double x = 2.0 * rand() / RAND_MAX - 1.0; 
        double y = 2.0 * rand() / RAND_MAX - 1.0;  

        // Si el punto esta dentro del circulo lo agrego a la variable
        if (x * x + y * y <= 1.0) {
            puntos_dentro_del_circulo++;
        }
    }

    // Aproximo el valor de pi
    double pi = 4.0 * puntos_dentro_del_circulo / NUM_PUNTOS;

    printf("Estimación de Pi: %.15f\n", pi);
    return 0;
}
