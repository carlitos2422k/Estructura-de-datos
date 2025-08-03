#include <iostream>
#include "Funcion.h"
#include "FuncionEjemplo.h"  // Incluir el nuevo archivo de cabecera

// Método para calcular el largo de la curva utilizando segmentos de recta
double largo(Funcion* f, double a, double b, int n) {
    // Inicializaciones
    double ancho = (b - a) / (n - 1);
    double ancho2 = ancho * ancho;
    double suma = 0;
    double x = a;
    double yant = f->valor(a);  // Evaluar la función en el punto inicial

    // Repetir n-1 veces para aproximar la longitud de la curva
    for (int i = 1; i < n; ++i) {
        // Evaluar la función en el siguiente punto
        x += ancho;
        double y = f->valor(x);
        
        // Calcular la longitud del segmento de recta
        double dif = y - yant;
        double l = std::sqrt(ancho2 + dif * dif);
        
        yant = y;  // Actualizar el valor anterior
        suma += l;  // Sumar la longitud del segmento
    }

    return suma;  // Retornar la suma de longitudes
}

int main() {
    // Crear un objeto de la función ejemplo (f(x) = sin(x))
    FuncionEjemplo funcion;

    // Definir el intervalo [a, b] y la cantidad de puntos n
    double a = 0;
    double b = M_PI;  // Intervalo [0, π]
    int n = 1000;  // Usar 1000 puntos para la aproximación

    // Calcular la longitud de la curva
    double resultado = largo(&funcion, a, b, n);

    // Imprimir el resultado
    std::cout << "La longitud aproximada de la curva es: " << resultado << std::endl;

    return 0;
}
