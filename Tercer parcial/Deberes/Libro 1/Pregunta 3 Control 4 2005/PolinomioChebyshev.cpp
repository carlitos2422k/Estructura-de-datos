#include "PolinomioChebyshev.h"

// Función que calcula el polinomio Chebyshev Tn(x) usando la fórmula recursiva
double PolinomioChebyshev::T(double x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    
    if (0 <= x && x <= 1) {
        return std::cos(n * arcoCoseno(x));  // Usar la fórmula Tn(x) = cos(n * arcoCoseno(x)) en [0, 1]
    }
    
    // Fórmula recursiva para el polinomio de Chebyshev
    return 2 * x * T(x, n - 1) - T(x, n - 2);
}

// Función que calcula el arcoCoseno de un valor x
double PolinomioChebyshev::arcoCoseno(double x) {
    if (x == 0) return M_PI / 2;  // Caso especial para x = 0
    
    return arcoTangente(std::sqrt(1 - x * x) / x);  // Usamos la fórmula arcoCoseno(x) = arcoTangente(sqrt(1 - x^2) / x)
}

// Función que calcula el arcoTangente usando la serie de Taylor
double PolinomioChebyshev::arcoTangente(double x) {
    double potencia = x, suma = x, sant = 0;
    
    // Calculamos la serie de Taylor de arcoTangente(x) hasta que la diferencia entre la suma actual y la anterior sea pequeña
    for (int i = 3; std::abs(suma - sant) > 0.00001; i += 2) {
        potencia *= -x * x;  // Alternamos el signo y elevamos x al cuadrado
        sant = suma;
        suma += potencia / i;  // Añadimos el siguiente término de la serie
    }
    
    return suma;
}
