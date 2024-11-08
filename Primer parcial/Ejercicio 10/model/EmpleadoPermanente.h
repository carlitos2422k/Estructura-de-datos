#ifndef EMPLEADOPERMANENTE_H
#define EMPLEADOPERMANENTE_H

#include "Empleado.h"

class EmpleadoPermanente : public Empleado {
public:
    EmpleadoPermanente(double salarioBase) : Empleado(salarioBase) {}

    double calcularBono() const override {
        return salarioBase * 0.1;  // 10% de bono
    }
};

#endif
