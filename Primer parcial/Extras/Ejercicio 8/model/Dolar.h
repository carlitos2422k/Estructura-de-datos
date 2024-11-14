#ifndef DOLAR_H
#define DOLAR_H

#include "Moneda.h"

class Dolar : public Moneda {
public:
    double convertirA(double cantidad) const override {
        return cantidad * 1.0;  // Asumiendo que la cantidad está en dólares
    }
};

#endif
