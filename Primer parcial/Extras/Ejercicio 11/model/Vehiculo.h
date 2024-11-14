#ifndef VEHICULO_H
#define VEHICULO_H

class Vehiculo {
public:
    virtual ~Vehiculo() = default;
    virtual int obtenerVelocidadMaxima() const = 0;
};

#endif
