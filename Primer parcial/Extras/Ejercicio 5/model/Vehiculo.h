#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>

class Vehiculo {
protected:
    std::string placa;
    std::string modelo;
public:
    Vehiculo(const std::string& placa, const std::string& modelo)
        : placa(placa), modelo(modelo) {}

    virtual double obtenerTarifaPorHora() const = 0;
    virtual ~Vehiculo() {}
};

#endif
