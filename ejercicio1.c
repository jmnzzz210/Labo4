#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para encontrar la secuencia más larga de 1's consecutivos
void findLargestLine(int **matrix, int SIZE, int *resultado) {
    int max = 0;
    int consecutivos = 0;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(*(*(matrix + i) + j) == 1) {
                consecutivos++;
                if(consecutivos > max) {
                    max = consecutivos;
                }
            } else {
                consecutivos = 0;
            }
        }
    }
    *resultado = max;
}

// Función para reservar la matriz en memoria dinámica
void allocateMatrix(int ***matrix, int SIZE) {
    *matrix = (int **)malloc(SIZE * sizeof(int *));
    if(*matrix == NULL) {
        printf("Error al reservar memoria para la matriz\n");
        exit(1);
    }
    for(int i = 0; i < SIZE; i++) {
        *(*matrix + i) = (int *)malloc(SIZE * sizeof(int));
        if(*(*matrix + i) == NULL) {
            printf("Error al reservar memoria para la fila %d\n", i);
            exit(1);
        }
    }
}

// Función para llenar la matriz con valores aleatorios entre 0 y 1
void fillMatrix(int **matrix, int SIZE) {
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            *(*(matrix + i) + j) = rand() % 2;
        }
    }
}

// Función para imprimir la matriz
void printMatrix(int **matrix, int SIZE) {
    printf("Matriz (%dx%d):\n", SIZE, SIZE);
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

// Función para liberar la memoria de la matriz
void freeMatrix(int **matrix, int SIZE) {
    for(int i = 0; i < SIZE; i++) {
        free(*(matrix + i));
    }
    free(matrix);
    matrix = NULL;
}

int main() {
    int SIZE, largestLine;
    int **matrix = NULL;
    
    printf("Digite el tamaño de la matriz deseado:");
    scanf("%d", &SIZE);

    allocateMatrix(&matrix, SIZE); // Se reserva la memoria de la matriz
    fillMatrix(matrix, SIZE); // Se genera la matriz
    printMatrix(matrix, SIZE); // Se imprime la matriz

    findLargestLine(matrix, SIZE, &largestLine); // Se busca la secuencia más larga de 1's
    printf("El tamaño de la secuencia de 1's más grande es: %d\n", largestLine);

    freeMatrix(matrix, SIZE); // Finalmente se libera el espacio

    return 0;
}
