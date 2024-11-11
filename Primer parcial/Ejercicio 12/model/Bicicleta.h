#ifndef BICICLETA_H
#define BICICLETA_H

#include "Vehiculo.h"

class Bicicleta : public Vehiculo {
private:
    double velocidad;

public:
    Bicicleta(double velocidad) : velocidad(velocidad) {}

    double calcularDistancia(double tiempo) const override {
        return velocidad * tiempo;
    }
};

#endif
