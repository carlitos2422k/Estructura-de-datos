#ifndef CALCULOVOLUMEN_H
#define CALCULOVOLUMEN_H

#include "Solido.h"
#include <iostream>

class CalculoVolumen {
public:
    void mostrarVolumen(const Solido& solido) const {
        std::cout << "Volumen: " << solido.calcularVolumen() << " unidades cúbicas" << std::endl;
    }
};

#endif
