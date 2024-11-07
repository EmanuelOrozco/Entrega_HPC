/*
Enunciado: 
Paralelizar una función que realiza operaciones matemáticas sobre matrices dinámicas utilizando OpenMP y punteros. 
Cada hilo debe trabajar en una parte de la matriz para realizar la operación más eficientemente.

Instrucciones:
    Implementar una función que reciba una matriz dinámica y realice una operación matemática (por ejemplo, multiplicar cada elemento por un valor constante).
    Utilizar OpenMP para paralelizar el proceso.
    Usar punteros para acceder y modificar los elementos de la matriz.
    Liberar la memoria al finalizar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void multiplicarMatriz(float **matriz, int filas, int columnas, float valor) {
    // Paralelizo el for para la multiplicacion de la matriz, y cada elemento lo multiplico por el valor ingresado
    #pragma omp parallel for
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] *= valor; 
        }
    }
}

// Funcion para imprimir la matriz
void imprimirMatriz(float **matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Funcion para liberar los punteros de la matriz
void liberarMatriz(float **matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        free(matriz[i]); // libero las filas
    }
    free(matriz);  // Libero el puntero a las filas
}

int main() {
    // Inicio las filas y columnas en una matriz por defecto de 3x3
    int filas = 3, columnas = 3;  
    float valor = 2.0; 

    // Creo una matriz dinamica pero sin datos
    float **matriz = (float **)malloc(filas * sizeof(float *));
    if (matriz == NULL) {
        printf("Error al asignar memoria para las filas de la matriz.\n");
        return 1;
    }

    for (int i = 0; i < filas; i++) {
        matriz[i] = (float *)malloc(columnas * sizeof(float));
        if (matriz[i] == NULL) {
            printf("Error al asignar memoria para las columnas de la matriz.\n");
            return 1;
        }
    }

    // Defino una matriz normal para iniciar los datos
    float matrizPorDefecto[3][3] = {
        {1.0, 2.0, 3.3},
        {4.5, 5.0, 6.0},
        {7.0, 8.0, 9.5}
    };

    // Inserto los valores de la matriz por defecto en la matriz dinamica
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = matrizPorDefecto[i][j];
        }
    }

    // Imprimo la matriz por defecto inicial
    printf("Matriz original:\n");
    imprimirMatriz(matriz, filas, columnas);

    // Multiplico la matriz por un valor (por default en 2.0)
    multiplicarMatriz(matriz, filas, columnas, valor);

    // Imprimo la matriz despues de la multiplicacion
    printf("\nMatriz después de multiplicar por %.2f:\n", valor);
    imprimirMatriz(matriz, filas, columnas);

    // Libero la memoria donde esta la matriz
    liberarMatriz(matriz, filas);

    return 0;
}
