#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000  // Para manejar frases largas

// Función para verificar si una cadena es palíndromo
bool esPalindromo(const char *str) {
    int inicio = 0;
    int fin = strlen(str) - 1;
    while (fin > inicio) {
        if (str[inicio++] != str[fin--]) {
            return false;
        }
    }
    return true;
}

// Función para procesar una línea (elimina no alfanuméricos y convierte a minúsculas)
void procesarLinea(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (isalnum((unsigned char)str[i])) {
            str[j++] = tolower((unsigned char)str[i]);
        }
        i++;
    }
    str[j] = '\0';
}

// Función principal
void encontrarPalindromoMasLargo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char linea[MAX_LINE_LENGTH];
    char *palindromoMasLargo = NULL;
    size_t longitudMasLarga = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        // Procesar cada línea (elimina espacios y signos)
        procesarLinea(linea);
        
        // Verificar si la línea procesada es palíndromo
        size_t longitud = strlen(linea);
        if (longitud > longitudMasLarga && esPalindromo(linea)) {
            free(palindromoMasLargo);
            palindromoMasLargo = strdup(linea);
            if (!palindromoMasLargo) {
                perror("Error de memoria");
                exit(EXIT_FAILURE);
            }
            longitudMasLarga = longitud;
        }
    }

    fclose(archivo);

    if (palindromoMasLargo) {
        printf("El palíndromo más largo es: %s (longitud: %zu)\n", palindromoMasLargo, longitudMasLarga);
        free(palindromoMasLargo);
    } else {
        printf("No se encontraron palíndromos.\n");
    }
}

int main() {
    encontrarPalindromoMasLargo("input.txt");
    return 0;
}