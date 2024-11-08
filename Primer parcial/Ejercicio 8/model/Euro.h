#ifndef EURO_H
#define EURO_H

#include "Moneda.h"

class Euro : public Moneda {
public:
    double convertirA(double cantidad) const override {
        return cantidad * 0.85;  // Conversión de dólar a euro
    }
};

#endif
