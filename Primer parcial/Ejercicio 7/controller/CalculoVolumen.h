#ifndef CALCULOVOLUMEN_H
#define CALCULOVOLUMEN_H

#include "Solido.h"

class CalculoVolumen {
public:
    double calcularVolumenSolido(const Solido& solido) const {
        return solido.calcularVolumen();
    }
};

#endif
