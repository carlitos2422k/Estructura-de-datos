#ifndef CARRO_H
#define CARRO_H

#include "Vehiculo.h"

class Carro : public Vehiculo {
private:
    double velocidad;

public:
    Carro(double velocidad) : velocidad(velocidad) {}

    double calcularDistancia(double tiempo) const override {
        return velocidad * tiempo;
    }
};

#endif
