/*******************************************************
 * Universidad de las Fuerzas Armadas ESPE             *
 * Departamento de Ciencias de la Computación          *
 * Autor: Carlos Pérez                                 *
 * Fecha: Viernes 1 de noviembre del 2024               *
 *******************************************************/
#include <iostream>
#include "../controller/OperacionesPerimetro.h"
using namespace std;
int main() {
    double ancho, largo;
    double radio;
    cout << "Ingrese el ancho del rectangulo:" ;
    cin >> ancho;
    cout << "Ingrese el largo del rectangulo: ";
    cin >> largo;
    cout << "Ingrese el radio del circulo: ";
    cin >> radio;
    Rectangulo rectangulo(ancho, largo);
    Circulo circulo(radio);

    std::cout << "Perimetro del rectangulo: " << OperacionesPerimetro::calcularPerimetroFigura(&rectangulo) << std::endl;
    std::cout << "Perimetro del circulo: " << OperacionesPerimetro::calcularPerimetroFigura(&circulo) << std::endl;

    return 0;
}
