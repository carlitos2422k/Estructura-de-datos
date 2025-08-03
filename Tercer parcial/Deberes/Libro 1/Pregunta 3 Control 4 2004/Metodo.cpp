#include "Metodo.h"
#include <cmath>

double Metodo::X(double Y, double a, double b, double epsilon, Funcion* f) {
    double x = (a + b) / 2;
    double y = f->evaluar(x);
    
    if (std::abs(Y - y) <= epsilon)
        return x;
    
    if (f->evaluar(a) < y)
        return (y < Y) ? X(Y, x, b, epsilon, f) : X(Y, a, x, epsilon, f);
    else
        return (y > Y) ? X(Y, x, b, epsilon, f) : X(Y, a, x, epsilon, f);
}
