#ifndef OPERACIONESESTACIONAMIENTO_H
#define OPERACIONESESTACIONAMIENTO_H

#include "../model/Vehiculo.h"

class OperacionesEstacionamiento {
public:
    static double calcularCosto(const Vehiculo& vehiculo, int horas) {
        return vehiculo.obtenerTarifaPorHora() * horas;
    }
};

#endif
