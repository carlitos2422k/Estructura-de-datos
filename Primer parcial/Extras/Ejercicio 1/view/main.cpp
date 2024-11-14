/*******************************************************
 * Universidad de las Fuerzas Armadas ESPE             *
 * Departamento de Ciencias de la Computación          *
 * Autor: Carlos Pérez                                 *
 * Fecha: Jueves 31 de octubre del 2024                *
 *******************************************************/

#include <iostream>
#include "../controller/OperacionesFigura.h"

int main() {
    double lado;
    double base,altura;
    int a;
    std::cout << "Ingrese la longitud de un lado del cuadrado: ";
    std::cin >> lado;
    std::cout << "Ingrese la base del triangulo: ";
    std::cin >> base;
    std::cout << "Ingrese la altura del triangulo: ";
    std::cin >> altura;
    Cuadrado cuadrado(lado);
    Triangulo triangulo(base,altura);
     
    std::cout << "Área del cuadrado: " << OperacionesFigura::calcularAreaFigura(&cuadrado) << std::endl;
    std::cout << "Área del triángulo: " << OperacionesFigura::calcularAreaFigura(&triangulo) << std::endl;

    return 0;
}
