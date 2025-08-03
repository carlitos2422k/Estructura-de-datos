#include "Minimo.h"
#include "Funcion.h"

// Función recursiva para encontrar el mínimo en el intervalo [a, b] usando búsqueda binaria
double xmin(double a, double b, double epsilon, const Funcion& f) {
    double p = (a + b) / 2;
    if (b - a < epsilon) {
        return p;  // Retorna el punto medio como el mínimo aproximado
    }

    double y1 = f.evaluar(p - epsilon / 2);
    double y2 = f.evaluar(p + epsilon / 2);

    if (y1 > y2) {
        return xmin(p, b, epsilon, f);  // Descartamos la mitad izquierda
    } else {
        return xmin(a, p, epsilon, f);  // Descartamos la mitad derecha
    }
}
