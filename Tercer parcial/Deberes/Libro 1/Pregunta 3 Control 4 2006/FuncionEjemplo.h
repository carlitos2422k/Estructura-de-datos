#ifndef FUNCION_EJEMPLO_H
#define FUNCION_EJEMPLO_H

#include "Funcion.h"
#include <cmath>

class FuncionEjemplo : public Funcion {
public:
    double valor(double x) override {
        return std::sin(x);  // Ejemplo: f(x) = sin(x)
    }
};

#endif
