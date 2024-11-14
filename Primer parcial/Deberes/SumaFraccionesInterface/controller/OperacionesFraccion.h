#ifndef OPERACIONESFRACCION_H
#define OPERACIONESFRACCION_H

#include "../model/Fraccion.h"
#include "ISumaFraccion.h"

class OperacionesFraccion : public ISumaFraccion {
public:
    FraccionConcreta sumar(const FraccionConcreta& fraccion1, const FraccionConcreta& fraccion2) override {
        int numeradorResultado = fraccion1.obtenerNumerador() * fraccion2.obtenerDenominador() +
                                 fraccion2.obtenerNumerador() * fraccion1.obtenerDenominador();
        int denominadorResultado = fraccion1.obtenerDenominador() * fraccion2.obtenerDenominador();

        return FraccionConcreta(numeradorResultado, denominadorResultado);
    }
};

#endif

