#ifndef OPERACIONESEMPLEADOS_H
#define OPERACIONESEMPLEADOS_H

#include "../model/Empleado.h"
#include <vector>

class OperacionesEmpleados {
public:
    static double calcularSalarioTotal(const std::vector<Empleado*>& empleados) {
        double total = 0;
        for (const auto& empleado : empleados) {
            total += empleado->calcularSalario();
        }
        return total;
    }
};

#endif
