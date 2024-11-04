#ifndef EMPLEADOTIEMPOCOMPLETO_H
#define EMPLEADOTIEMPOCOMPLETO_H

#include "Empleado.h"

class EmpleadoTiempoCompleto : public Empleado {
private:
    double salarioMensual;
public:
    EmpleadoTiempoCompleto(const std::string& nombre, double salarioMensual)
        : Empleado(nombre), salarioMensual(salarioMensual) {}

    double calcularSalario() const override {
        return salarioMensual;
    }
};

#endif
