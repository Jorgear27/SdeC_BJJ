#include <stdio.h>
#include <stdlib.h>

extern int procesar_gini(float valor);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <gini>\n", argv[0]);
        return 1;
    }

    float gini = atof(argv[1]);
    int resultado = procesar_gini(gini);
    printf("%d\n", resultado);
    return 0;
}
