#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración de las funciones en ensamblador
extern long suma(long a, long b);     // Función de suma en ensamblador
extern long resta(long a, long b);    // Función de resta en ensamblador
extern long mul(long a, long b);      // Función de multiplicación en ensamblador
extern long division(long a, long b); // Función de división en ensamblador

int main(int argc, char *argv[]) {
    // Verificación de que se proporcionaron suficientes argumentos
    if (argc < 4) {
        printf("Uso: %s <a> <b> <operacion>\n", argv[0]);
        return 1;  // Retorna 1 si no se pasan los argumentos necesarios
    }

    // Conversión de los argumentos de la línea de comandos a números
    long a = atol(argv[1]);  // Convierte el primer argumento a un número largo
    long b = atol(argv[2]);  // Convierte el segundo argumento a un número largo
    char *op = argv[3];      // El tercer argumento es la operación a realizar
    long res = 0;            // Inicializa la variable para almacenar el resultado

    // Comparación de la operación y ejecución correspondiente
    if (strcmp(op, "suma") == 0)  // Si la operación es 'suma'
        res = suma(a, b);         // Llama a la función suma
    else if (strcmp(op, "resta") == 0)  // Si la operación es 'resta'
        res = resta(a, b);            // Llama a la función resta
    else if (strcmp(op, "mul") == 0)    // Si la operación es 'mul'
        res = mul(a, b);              // Llama a la función multiplicación
    else if (strcmp(op, "div") == 0)    // Si la operación es 'div'
        res = division(a, b);         // Llama a la función división
    else {  
        printf("Operación no válida.\n");  // Si la operación no es válida
        return 1;  // Retorna 1 para indicar error
    }

    // Muestra el resultado de la operación
    printf("%ld\n", res);
    return 0;  // Retorna 0 para indicar éxito
}

