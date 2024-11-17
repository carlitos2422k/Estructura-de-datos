#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <cctype>

// Usando 'extern "C"' para evitar el mangling de nombres
extern "C" {

__declspec(dllexport) int ingresar(char *msj) {
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);
    while ((c = getch()) != 13) {  // Enter
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {  // Backspace
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0';
    valor = atoi(cad);
    return valor;
}

__declspec(dllexport) char ingresarLetra(char *msj) {
    char c;
    printf("%s", msj);
    while (true) {
        c = getch();
        if (isalpha(c)) {
            printf("%c", c);
            return c;
        } else if (c == 8) {  // Backspace
            printf("\b \b");
        }
    }
}

__declspec(dllexport) float ingresarFloat(char *msj) {
    char cad[10];
    char c;
    int i = 0;
    float valor = 0;
    printf("%s", msj);
    while ((c = getch()) != 13) {  // Enter
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {  // Backspace
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (c == 46) {  // Punto
            bool aux = false;
            for (int j = 0; cad[j] != '\0'; j++) {
                if (cad[j] == 46) {
                    aux = true;
                    break;
                }
            }
            if (!aux) {
                printf("%c", c);
                cad[i++] = c;
            }
        }
    }
    cad[i] = '\0';
    valor = atof(cad);
    return valor;
}

__declspec(dllexport) const char* ingresarString(char *msj) {
    static char cad[100];  // Memoria estática para la cadena
    char c;
    int i = 0;
    printf("%s", msj);
    while ((c = getch()) != 13) {  // Enter
        if (isalpha(c)) {
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {  // Backspace
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0';
    return cad;
}

__declspec(dllexport) double ingresarDouble(char *msj) {
    char cad[20];
    char c;
    int i = 0;
    double valor = 0;
    printf("%s", msj);
    while ((c = getch()) != 13) {  // Enter
        if ((c >= '0' && c <= '9') || c == '.') {
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8 && i > 0) {  // Backspace
            printf("\b \b");
            i--;
        }
    }
    cad[i] = '\0';
    valor = atof(cad);
    return valor;
}

}
