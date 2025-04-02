#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// GRUPO: JULIANA TUTA Y ANGEL FABIAN PEDREROS
// Separa los coeficientes y los suma en un arreglo donde su posición es el exponente al que pertenece

void sep_sumar(const char* argv, int pol[]) {
    int exp = 0, signo = 1, coef = 0, i = 0;
    while (i < strlen(argv)) {
        if (argv[i] == '+') {
            signo = 1;
            i++;
        }
        else if (argv[i] == '-') {
            i++;
            signo = -1;
        }
        else if (isdigit(argv[i])) {
            coef = strtol(&argv[i], NULL, 10) * signo;
            while (i < strlen(argv) && isdigit(argv[i])) i++;
        }
        else {
            coef = signo;
        }
        
        if (i < strlen(argv) && argv[i] == 'x') {
            i++;
            if (i < strlen(argv) && argv[i] == '^') {
                i++;
                exp = strtol(&argv[i], NULL, 10);
                while (i < strlen(argv) && isdigit(argv[i])) i++;
            }
            else {
                exp = 1;
            }
        }
        else {
            exp = 0;
        }
        
        pol[exp] += coef;
        coef = 0;
    }
}

// Imprime el polinomio resultante
void imprimirres(const int pol[]) {
    bool primerdigito = false;
    for (int i = 9; i >= 0; i--) {
        if (pol[i] != 0) {
            if (!primerdigito) {
                if (i == 0) {
                    printf("%d", pol[i]);
                } 
                else if (i == 1) {
                    if (pol[i] == 1) {
                        printf("x");
                    } 
                    else if (pol[i] == -1) {
                        printf("-x");
                    }
                    else {
                        printf("%dx", pol[i]);
                    }
                } 
                else {
                    if (pol[i] == 1) {
                        printf("x^%d", i);
                    } 
                    else if (pol[i] == -1) {
                        printf("-x^%d", i);
                    }
                    else {
                        printf("%dx^%d", pol[i], i);
                    }
                }
                primerdigito = true;
            }
            else {
                if (i == 0) {
                    if (pol[i] > 0) {
                        printf(" + %d", pol[i]);
                    } 
                    else {
                        printf(" - %d", -pol[i]);
                    }
                } 
                else if (i == 1) {
                    if (pol[i] == 1) {
                        printf(" + x");
                    } 
                    else if (pol[i] == -1) {
                        printf(" - x");
                    }
                    else if (pol[i] > 0) {
                        printf(" + %dx", pol[i]);
                    } 
                    else {
                        printf(" - %dx", -pol[i]);
                    }
                } 
                else {
                    if (pol[i] == 1) {
                        printf(" + x^%d", i);
                    } 
                    else if (pol[i] == -1) {
                        printf(" - x^%d", i);
                    }
                    else if (pol[i] > 0) {
                        printf(" + %dx^%d", pol[i], i);
                    } 
                    else {
                        printf(" - %dx^%d", -pol[i], i);
                    }
                }
            }
        }
    }
    
    // Si no hay términos, imprime 0
    if (!primerdigito) {
        printf("0");
    }
}

int main(int argc, char* argv[]) {
    int pol[10] = {0};
    
    if (argc < 2) {
        printf("Uso: %s \"polinomio1\" \"polinomio2\" ...\n", argv[0]);
        printf("Ejemplo: %s \"3x^2+4x-5\" \"x^3-2x+1\"\n", argv[0]);
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        sep_sumar(argv[i], pol);
    }
    
    imprimirres(pol);
    printf("\n");
    
    return 0;
}