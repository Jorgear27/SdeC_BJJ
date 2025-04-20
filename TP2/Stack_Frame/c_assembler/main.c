#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern long suma(long a, long b);
extern long resta(long a, long b);
extern long mul(long a, long b);
extern long division(long a, long b);

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s <a> <b> <operacion>\n", argv[0]);
        return 1;
    }

    long a = atol(argv[1]);
    long b = atol(argv[2]);
    char *op = argv[3];
    long res = 0;

    if (strcmp(op, "suma") == 0)
        res = suma(a, b);
    else if (strcmp(op, "resta") == 0)
        res = resta(a, b);
    else if (strcmp(op, "mul") == 0)
        res = mul(a, b);
    else if (strcmp(op, "div") == 0)
        res = division(a, b);
    else {
        printf("Operación no válida.\n");
        return 1;
    }

    printf("%ld\n", res);
    return 0;
}
