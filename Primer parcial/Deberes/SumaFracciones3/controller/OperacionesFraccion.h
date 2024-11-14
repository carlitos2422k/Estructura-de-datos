#ifndef OPERACIONESFRACCION_H
#define OPERACIONESFRACCION_H

#include "ISumaFraccion.h"
#include "../model/Fraccion.h"

template <typename T>
class OperacionesFraccion : public ISumaFraccion<T> {
public:
    T sumar(const T& fraccion1, const T& fraccion2) override {
        int numeradorResultado = fraccion1.obtenerNumerador() * fraccion2.obtenerDenominador() +
                                 fraccion2.obtenerNumerador() * fraccion1.obtenerDenominador();
        int denominadorResultado = fraccion1.obtenerDenominador() * fraccion2.obtenerDenominador();

        return T(numeradorResultado, denominadorResultado);
    }
};

#endif



