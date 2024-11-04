#ifndef MOTO_H
#define MOTO_H

#include "Vehiculo.h"

class Moto : public Vehiculo {
public:
    Moto(const std::string& placa, const std::string& modelo)
        : Vehiculo(placa, modelo) {}

    double obtenerTarifaPorHora() const override {
        return 1.0; 
    }
};

#endif
