#ifndef ESFERA_H
#define ESFERA_H

#include "Solido.h"

class Esfera : public Solido {
private:
    double radio;

public:
    Esfera(double radio) : radio(radio) {}

    double calcularVolumen() const override {
        return (4.0 / 3.0) * 3.14159 * radio * radio * radio;
    }
};

#endif
