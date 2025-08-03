#include <iostream>
#include "Area.h"
#include "Funciones.h"

int main() {
    // Crear instancias de las funciones f(x) y g(x)
    F* f = new FuncionF();
    F* g = new FuncionG();

    // Definir el intervalo [a, b] y el número de puntos n
    double a = 0.0, b = 5.0;
    int n = 1000;
    double eps = 0.0001;  // Tolerancia para la raíz

    // Calcular el área combinada
    double resultado = Area::area(f, g, a, b, n, eps);

    // Mostrar el resultado
    std::cout << "El área combinada es: " << resultado << std::endl;

    // Limpiar la memoria
    delete f;
    delete g;

    return 0;
}
