#ifndef CONVERTIDORMONEDA_H
#define CONVERTIDORMONEDA_H

#include "Moneda.h"

class ConvertidorMoneda {
public:
    double convertir(const Moneda& moneda, double cantidad) const {
        return moneda.convertirA(cantidad);
    }
};

#endif
