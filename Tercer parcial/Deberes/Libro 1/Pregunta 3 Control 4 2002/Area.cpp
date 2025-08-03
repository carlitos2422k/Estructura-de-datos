#include "Area.h"

// Método para calcular la raíz de f - g
double Area::raiz(F* f, F* g, double a, double b, double eps) {
    double x = (a + b) / 2;
    if (b - a <= eps)
        return x;
    if (signo(f->valor(a) - g->valor(a)) == signo(f->valor(x) - g->valor(x)))
        return raiz(f, g, x, b, eps);
    else
        return raiz(f, g, a, x, eps);
}

// Método para determinar el signo de una función
int Area::signo(double x) {
    return (x < 0) ? -1 : 1;
}

// Método para calcular la integral de una función
double Area::integral(F* f, double a, double b, int n) {
    double s = 0, x = a, ancho = (b - a) / n;
    for (int i = 1; i <= n; ++i) {
        s += f->valor(x);
        x += ancho;
    }
    return s * ancho;
}

// Método principal para calcular el área combinada
double Area::area(F* f, F* g, double a, double b, int n, double eps) {
    // Calcular la raíz (punto de intersección)
    double m = raiz(f, g, a, b, eps);

    // Asegurarse de que f > g en [a, m]
    if (f->valor(a) < g->valor(a)) {
        F* aux = f;
        f = g;
        g = aux;
    }

    // Calcular área en [a, m]
    double factor = (m - a) / (b - a);
    int n1 = static_cast<int>(n * factor);
    double area1 = integral(f, a, m, n1);

    // Calcular área en [m, b]
    int n2 = n - n1;
    double area2 = integral(g, m, b, n2);

    // Devolver el área total
    return area1 + area2;
}
