#ifndef EMPLEADOTEMPORAL_H
#define EMPLEADOTEMPORAL_H

#include "Empleado.h"

class EmpleadoTemporal : public Empleado {
public:
    EmpleadoTemporal(double salarioBase) : Empleado(salarioBase) {}

    double calcularBono() const override {
        return salarioBase * 0.05;  // 5% de bono
    }
};

#endif
