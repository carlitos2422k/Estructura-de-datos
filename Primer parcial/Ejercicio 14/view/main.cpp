#include <iostream>
#include "model/Triangulo.h"
#include "controller/CalculoFigura.h"

int main() {
    double lado1, lado2, lado3;
    std::cout << "Ingrese los tres lados del triángulo: ";
    std::cin >> lado1 >> lado2 >> lado3;

    Triangulo triangulo(lado1, lado2, lado3);
    CalculoFigura calculo;

    calculo.mostrarCalculos(triangulo);

    return 0;
}
