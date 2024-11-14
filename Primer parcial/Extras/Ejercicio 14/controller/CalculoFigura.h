#ifndef CALCULOFIGURA_H
#define CALCULOFIGURA_H

#include "Figura.h"

class CalculoFigura {
public:
    void mostrarCalculos(const Figura& figura) const {
        std::cout << "Área: " << figura.calcularArea() << std::endl;
        std::cout << "Perímetro: " << figura.calcularPerimetro() << std::endl;
    }
};

#endif

