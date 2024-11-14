#ifndef ISUMAFRACCION_H
#define ISUMAFRACCION_H

#include "../model/Fraccion.h"

class ISumaFraccion {
public:
    virtual FraccionConcreta sumar(const FraccionConcreta& fraccion1, const FraccionConcreta& fraccion2) = 0;
    virtual ~ISumaFraccion() = default; // Destructor virtual para garantizar la correcta destrucción de subclases
};

#endif
