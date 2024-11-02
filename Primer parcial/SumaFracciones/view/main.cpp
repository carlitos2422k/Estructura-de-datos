#include <iostream>
#include "../model/Fraccion.h"
#include "../controller/OperacionesFraccion.h"

int main() {
    int numerador1, denominador1;
    int numerador2, denominador2;

   
    std::cout << "Ingrese el numerador de la primera fracción: ";
    std::cin >> numerador1;
    std::cout << "Ingrese el denominador de la primera fracción: ";
    std::cin >> denominador1;

   
    std::cout << "Ingrese el numerador de la segunda fracción: ";
    std::cin >> numerador2;
    std::cout << "Ingrese el denominador de la segunda fracción: ";
    std::cin >> denominador2;

    
    FraccionConcreta fraccion1(numerador1, denominador1);
    FraccionConcreta fraccion2(numerador2, denominador2);

   
    FraccionConcreta resultado = OperacionesFraccion::sumar(fraccion1, fraccion2);

    
    std::cout << "Resultado de la suma: "
              << resultado.obtenerNumerador() << "/"
              << resultado.obtenerDenominador() << std::endl;

    return 0;
}
