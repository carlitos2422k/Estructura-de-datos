#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>

class Empleado {
protected:
    std::string nombre;
public:
    Empleado(const std::string& nombre) : nombre(nombre) {}
    virtual double calcularSalario() const = 0;
    virtual ~Empleado() {} 
};

#endif
