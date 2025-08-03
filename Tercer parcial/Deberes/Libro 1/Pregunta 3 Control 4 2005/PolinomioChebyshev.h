#ifndef POLINOMIOCHEBYSHEV_H
#define POLINOMIOCHEBYSHEV_H

#include <cmath>

class PolinomioChebyshev {
public:
    static double T(double x, int n);  // Calcula Tn(x)
    static double arcoCoseno(double x);  // Calcula arcoCoseno(x)
    static double arcoTangente(double x);  // Calcula arcoTangente(x)
};

#endif
