#ifndef PRODUCTOALIMENTO_H
#define PRODUCTOALIMENTO_H

#include "Producto.h"

class ProductoAlimento : public Producto {
private:
    double precioBase;
public:
    ProductoAlimento(double precio) : precioBase(precio) {}

    double obtenerPrecio() const override {
        return precioBase;
    }
};

#endif
