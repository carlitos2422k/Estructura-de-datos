#ifndef EMPLEADO_H
#define EMPLEADO_H

class Empleado {
protected:
    double salarioBase;

public:
    Empleado(double salarioBase) : salarioBase(salarioBase) {}

    virtual ~Empleado() = default;

    virtual double calcularBono() const = 0;
};

#endif
