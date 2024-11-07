/*
Ejercicio 1: 
Introducción a Regiones Paralelas - 

Escribe un programa en C que cree una región paralela utilizando 4 hilos. 
Cada hilo debe imprimir su número de identificación (ID) y un mensaje de "Hola desde el hilo X". 
Usa la función omp_get_thread_num() para obtener el ID del hilo.
*/

// Comando en bash para ejecutar el codigo: ./Ejercicio_1

#include <stdio.h>
#include <omp.h>

int main() {
    // Coloco que el numero de hilos sea de 4
    omp_set_num_threads(4);

    // Inicio la seccion paralela
    #pragma omp parallel
    {
        // Creo una variable para guardar el numero de hilo en el que esta y despues la imprimo
        int thread_id = omp_get_thread_num();

        printf("Codigo desde el hilo %d\n", thread_id);
    }

    return 0;
}
