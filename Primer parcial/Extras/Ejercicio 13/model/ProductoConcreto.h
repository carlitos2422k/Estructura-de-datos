#ifndef PRODUCTOCONCRETO_H
#define PRODUCTOCONCRETO_H

#include "Producto.h"

class ProductoConcreto : public Producto {
public:
    ProductoConcreto(double precioBase) : Producto(precioBase) {}

    double calcularPrecioConImpuesto() const override {
        return precioBase * 1.12; // Agregar el 12% de impuesto
    }
};

#endif
