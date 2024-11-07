/*
Ejercicio 5: 
Control de Variables Privadas y Compartidas - 

Escribe un programa que inicialice una variable total en 0. 
Luego, dentro de una región paralela con 4 hilos, cada hilo debe sumar un número diferente (por ejemplo, 1, 2, 3 o 4) a la variable total. 
Utiliza las cláusulas private y shared para manejar correctamente las variables.
*/

#include <stdio.h>
#include <omp.h>

int main() {
    int total = 0;  // Variable compartida para almacenar el total
    int num;        // Variable privada para cada hilo (número que cada hilo sumará)

    // Inicio una seccion paralela que usara solo 4 hilos, pongo la variable num como privada y la variable total como compartida
    #pragma omp parallel num_threads(4) private(num) shared(total)
    {
        // Creo una variable para almacenar el id del hilo en el que esta
        int thread_id = omp_get_thread_num(); 

        // Asigno los numeros a 'num' según el id del hilo
        if (thread_id == 0) {
            num = 1;
        } else if (thread_id == 1) {
            num = 2;
        } else if (thread_id == 2) {
            num = 3;
        } else if (thread_id == 3) {
            num = 4;
        }

        // Sumar el número al total, y con atomic me aseguro de que no hayan condiciones de carrera
        #pragma omp atomic
        total += num; 
    }
    
    // Imprimo el total
    printf("El total calculado es: %d\n", total);

    return 0;
}
