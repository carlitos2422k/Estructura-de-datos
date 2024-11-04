#ifndef CIRCULO_H
#define CIRCULO_H

#include "Figura.h"
#include <cmath>

class Circulo : public Figura {
private:
    double radio;
public:
    Circulo(double radio) : radio(radio) {}
    double calcularPerimetro() const override {
        return 2 * M_PI * radio;
    }
};

#endif
