#ifndef SENO_H
#define SENO_H

#include "Funcion.h"
#include <cmath>

class Seno : public Funcion {
public:
    double evaluar(double x) override {
        return std::sin(x);
    }
};

#endif
