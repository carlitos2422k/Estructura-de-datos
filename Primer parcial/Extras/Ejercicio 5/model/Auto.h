#ifndef AUTO_H
#define AUTO_H

#include "Vehiculo.h"

class Auto : public Vehiculo {
public:
    Auto(const std::string& placa, const std::string& modelo)
        : Vehiculo(placa, modelo) {}

    double obtenerTarifaPorHora() const override {
        return 2.0; 
    }
};

#endif
