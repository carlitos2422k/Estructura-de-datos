#ifndef VEHICULO_H
#define VEHICULO_H

class Vehiculo {
public:
    virtual ~Vehiculo() = default;
    virtual double calcularDistancia(double tiempo) const = 0;
};

#endif
