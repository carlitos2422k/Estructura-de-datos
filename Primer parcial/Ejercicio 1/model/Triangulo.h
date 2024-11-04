#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "FiguraGeometrica.h"

class Triangulo : public FiguraGeometrica {
private:
    double base, altura;
public:
    Triangulo(double base, double altura) : base(base), altura(altura) {}
    double calcularArea() const override {
        return (base * altura) / 2;
    }
};

#endif
