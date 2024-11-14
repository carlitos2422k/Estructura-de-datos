#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Figura.h"
#include <cmath>

class Triangulo : public Figura {
private:
    double lado1, lado2, lado3;

public:
    Triangulo(double l1, double l2, double l3) : lado1(l1), lado2(l2), lado3(l3) {}

    double calcularPerimetro() const override {
        return lado1 + lado2 + lado3;
    }

    double calcularArea() const override {
        double s = calcularPerimetro() / 2;
        return std::sqrt(s * (s - lado1) * (s - lado2) * (s - lado3)); // Fórmula de Herón
    }
};

#endif
