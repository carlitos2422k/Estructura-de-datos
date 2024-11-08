#ifndef CALCULONOTA_H
#define CALCULONOTA_H

#include "Calificacion.h"

class CalculoNota {
public:
    double calcular(const Calificacion& calificacion) const {
        return calificacion.calcularNotaFinal();
    }
};

#endif
