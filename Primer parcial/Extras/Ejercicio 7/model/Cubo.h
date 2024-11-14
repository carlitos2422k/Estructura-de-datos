#ifndef CUBO_H
#define CUBO_H

#include "Solido.h"

class Cubo : public Solido {
private:
    double lado;

public:
    Cubo(double lado) : lado(lado) {}

    double calcularVolumen() const override {
        return lado * lado * lado;
    }
};

#endif
