#include <iostream>
#include "PolinomioChebyshev.h"

int main() {
    double x;
    int n;
    
    // Solicitar entrada del usuario para x y n
    std::cout << "Ingrese el valor de x (en el intervalo [0,1]): ";
    std::cin >> x;
    
    std::cout << "Ingrese el valor de n (grado del polinomio): ";
    std::cin >> n;
    
    // Calcular y mostrar el polinomio Chebyshev Tn(x)
    double resultado = PolinomioChebyshev::T(x, n);
    
    std::cout << "El valor de T" << n << "(" << x << ") es: " << resultado << std::endl;
    
    return 0;
}
