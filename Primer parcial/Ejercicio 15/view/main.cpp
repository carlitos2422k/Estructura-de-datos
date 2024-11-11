#include <iostream>
#include "model/Cubo.h"
#include "controller/CalculoVolumen.h"

int main() {
    double lado;
    std::cout << "Ingrese el lado del cubo: ";
    std::cin >> lado;

    Cubo cubo(lado);
    CalculoVolumen calculo;

    calculo.mostrarVolumen(cubo);

    return 0;
}
