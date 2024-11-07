/*
Ejercicio 4: 
Secciones Paralelas - 

Escribe un programa que cree dos secciones paralelas. 
En la primera sección, se debe imprimir la tabla de multiplicar del 2, y en la segunda sección, la tabla de multiplicar del 3. 
Cada sección debe ser ejecutada por un hilo diferente.
*/

#include <stdio.h>
#include <omp.h>

int main() {
    // Inicio una seccion paralela principal la cual tiene secciones paralelas dentro, con hilos distintos
    #pragma omp parallel sections
    {
        // Primera seccion: imprime la tabla de multiplicar del 2
        #pragma omp section
        {
            printf("Tabla de multiplicar del 2:\n");
            for (int i = 1; i <= 10; i++) {
                printf("2 x %d = %d\n", i, 2 * i);
            }
        }

        // Segunda seccion: imprime la tabla de multiplicar del 3
        #pragma omp section
        {
            printf("\nTabla de multiplicar del 3:\n");
            for (int i = 1; i <= 10; i++) {
                printf("3 x %d = %d\n", i, 3 * i);
            }
        }
    }

    return 0;
}
