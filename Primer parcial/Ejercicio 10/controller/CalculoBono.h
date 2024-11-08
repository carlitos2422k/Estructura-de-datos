#ifndef CALCULOBONO_H
#define CALCULOBONO_H

#include "Empleado.h"

class CalculoBono {
public:
    double calcular(const Empleado& empleado) const {
        return empleado.calcularBono();
    }
};

#endif
