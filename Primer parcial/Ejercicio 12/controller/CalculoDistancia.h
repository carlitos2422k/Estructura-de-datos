#ifndef CALCULODISTANCIA_H
#define CALCULODISTANCIA_H

#include "Vehiculo.h"

class CalculoDistancia {
public:
    double mostrarDistancia(const Vehiculo& vehiculo, double tiempo) const {
        return vehiculo.calcularDistancia(tiempo);
    }
};

#endif
