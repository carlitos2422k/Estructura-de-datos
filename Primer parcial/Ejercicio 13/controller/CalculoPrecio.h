#ifndef CALCULOPRECIO_H
#define CALCULOPRECIO_H

#include "Producto.h"

class CalculoPrecio {
public:
    double mostrarPrecioFinal(const Producto& producto) const {
        return producto.calcularPrecioConImpuesto();
    }
};

#endif
