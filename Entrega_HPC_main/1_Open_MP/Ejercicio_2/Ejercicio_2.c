/*
Ejercicio 2: 
Control de Número de Hilos - 

Escribe un programa que determine el número máximo de hilos disponibles en tu sistema utilizando omp_get_num_procs(). 
Luego, ajusta el número de hilos a la mitad de ese valor y crea una región paralela donde cada hilo imprima su número de 
identificación y el número total de hilos en ejecución.
*/

#include <stdio.h>
#include <omp.h>

int main() {
    // Creo una variable en la cual guardo la cantidad de procesadores del equipo, y despues divido la cantidad en 2
    int num_procs = omp_get_num_procs();
    int num_threads = num_procs / 2;

    // Ajusto la cantidad de hilos con los procesadores disponibles
    omp_set_num_threads(num_threads);

    // Imprimo los procesadores disponibles al incio y con cuantos se va a trabajar el codigo
    printf("Numero de procesadores en el equipo: %d\n", num_procs);
    printf("Numero de hilos que se usaran (mitad de procesadores): %d\n", num_threads);

    // Inicio la seccion paralela
    #pragma omp parallel
    {
        // Obtengo el ID del hilo y el número total de hilos y los imprimo posteriormente
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hola desde el hilo con id %d de %d hilos.\n", thread_id, total_threads);
    }

    return 0;
}
