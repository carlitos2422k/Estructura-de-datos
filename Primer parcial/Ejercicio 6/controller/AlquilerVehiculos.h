#ifndef ALQUILERVEHICULOS_H
#define ALQUILERVEHICULOS_H

#include "Vehiculo.h"

class AlquilerVehiculos {
public:
    double calcularTarifaTotal(const Vehiculo& vehiculo, int dias) const {
        return vehiculo.getTarifa() * dias;
    }
};

#endif
