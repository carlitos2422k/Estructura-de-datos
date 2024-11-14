#ifndef RECTANGULO_H
#define RECTANGULO_H

#include "Figura.h"

class Rectangulo : public Figura {
private:
    double largo, ancho;
public:
    Rectangulo(double largo, double ancho) : largo(largo), ancho(ancho) {}
    double calcularPerimetro() const override {
        return 2 * (largo + ancho);
    }
};

#endif
