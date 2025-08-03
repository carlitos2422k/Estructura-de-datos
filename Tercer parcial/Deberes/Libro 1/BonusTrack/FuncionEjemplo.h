#ifndef FUNCIONEJEMPLO_H
#define FUNCIONEJEMPLO_H

#include "Funcion.h"
#include <cmath>

class FuncionEjemplo : public Funcion {
public:
    double valor(double x) const override {
        // Ejemplo: f(x) = x^2
        return x * x;
    }
};

#endif
