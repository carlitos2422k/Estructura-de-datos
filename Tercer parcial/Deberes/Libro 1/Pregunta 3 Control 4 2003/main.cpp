#include <iostream>
#include "Seno.h"
#include "Minimo.h"
#include <cmath>

int main() {
    // Definir el intervalo [π, 2π] y la precisión epsilon
    double a = M_PI;
    double b = 2 * M_PI;
    double epsilon = 0.001;

    // Crear el objeto Seno
    Seno seno;

    // Llamar a la función para obtener el valor mínimo
    double resultado = xmin(a, b, epsilon, seno);

    // Mostrar el resultado con 3 decimales de precisión
    std::cout << "El mínimo de seno en el intervalo [" << a << ", " << b << "] es en x = " << resultado << std::endl;

    return 0;
}
