#ifndef CARRO_H
#define CARRO_H

#include "Vehiculo.h"

class Carro : public Vehiculo {
private:
    int velocidadMaxima;

public:
    Carro(int velocidad) : velocidadMaxima(velocidad) {}

    int obtenerVelocidadMaxima() const override {
        return velocidadMaxima;
    }
};

#endif
