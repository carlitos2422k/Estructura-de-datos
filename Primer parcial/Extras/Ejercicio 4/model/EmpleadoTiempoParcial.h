#ifndef EMPLEADOTIEMPOPARCIAL_H
#define EMPLEADOTIEMPOPARCIAL_H

#include "Empleado.h"

class EmpleadoTiempoParcial : public Empleado {
private:
    double tarifaPorHora;
    int horasTrabajadas;
public:
    EmpleadoTiempoParcial(const std::string& nombre, double tarifa, int horas)
        : Empleado(nombre), tarifaPorHora(tarifa), horasTrabajadas(horas) {}

    double calcularSalario() const override {
        return tarifaPorHora * horasTrabajadas;
    }
};

#endif
