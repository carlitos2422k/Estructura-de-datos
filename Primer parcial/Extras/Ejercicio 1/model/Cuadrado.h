#ifndef CUADRADO_H
#define CUADRADO_H

#include "FiguraGeometrica.h"

class Cuadrado : public FiguraGeometrica {
private:
    double lado;
public:
    Cuadrado(double lado) : lado(lado) {}
    double calcularArea() const override {
        return lado * lado;
    }
};

#endif
