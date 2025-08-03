#include <iostream>
#include "Metodos.h"
#include "FuncionEjemplo.h"

int main() {
    FuncionEjemplo f;
    FuncionEjemplo g;

    double a = 0, b = 1;
    int n = 1000;

    // Calcular la integral combinada
    double area_resultado = area(f, g, a, b, n);
    std::cout << "Resultado de la integral combinada: " << area_resultado << std::endl;

    // Calcular el mínimo absoluto
    double min_resultado = minx(a, b, 0.0001, f);
    std::cout << "Resultado del mínimo absoluto: " << min_resultado << std::endl;

    // Aproximar X(Y)
    double Y = 0.5;
    double X_resultado = X(Y, a, b, 0.0001, f);
    std::cout << "Resultado de X(Y): " << X_resultado << std::endl;

    // Calcular el valor del polinomio de Chebyshev
    int n_pol = 3;
    double T_resultado = T(0.5, n_pol);
    std::cout << "Resultado del polinomio de Chebyshev: " << T_resultado << std::endl;

    // Calcular el largo de la curva
    double largo_resultado = largo(f, a, b, n);
    std::cout << "Resultado del largo de la curva: " << largo_resultado << std::endl;

    return 0;
}
