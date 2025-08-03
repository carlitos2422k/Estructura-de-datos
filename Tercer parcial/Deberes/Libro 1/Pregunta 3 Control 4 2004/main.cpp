#include <iostream>
#include <cmath>
#include "Seno.h"
#include "Metodo.h"

int main() {
    Seno seno;  // Crear el objeto Seno
    double Y = 0.333;  // Valor que queremos encontrar
    double epsilon = 0.001;  // Precisión deseada
    
    // Llamar al método X para calcular el valor de X
    double x_resultado = Metodo::X(Y, 0, M_PI / 2, epsilon, &seno);
    
    // Imprimir el valor de coseno de X
    std::cout << "El valor de cos(X) es: " << std::cos(x_resultado) << std::endl;
    
    return 0;
}
