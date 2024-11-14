#ifndef CALCULOVELOCIDAD_H
#define CALCULOVELOCIDAD_H

#include "Vehiculo.h"

class CalculoVelocidad {
public:
    int mostrarVelocidad(const Vehiculo& vehiculo) const {
        return vehiculo.obtenerVelocidadMaxima();
    }
};

#endif
