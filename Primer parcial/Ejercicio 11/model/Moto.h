#ifndef MOTO_H
#define MOTO_H

#include "Vehiculo.h"

class Moto : public Vehiculo {
private:
    int velocidadMaxima;

public:
    Moto(int velocidad) : velocidadMaxima(velocidad) {}

    int obtenerVelocidadMaxima() const override {
        return velocidadMaxima;
    }
};

#endif
