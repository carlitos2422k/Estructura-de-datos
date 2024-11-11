#ifndef CUBO_H
#define CUBO_H

#include "Solido.h"

class Cubo : public Solido {
private:
    double lado;

public:
    Cubo(double l) : lado(l) {}

    double calcularVolumen() const override {
        return lado * lado * lado; // Fórmula del volumen de un cubo
    }
};

#endif
