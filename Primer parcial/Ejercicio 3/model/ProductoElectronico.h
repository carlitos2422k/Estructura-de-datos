#ifndef PRODUCTOELECTRONICO_H
#define PRODUCTOELECTRONICO_H

#include "Producto.h"

class ProductoElectronico : public Producto {
private:
    double precioBase;
    double impuesto;
public:
    ProductoElectronico(double precio, double impuesto)
        : precioBase(precio), impuesto(impuesto) {}

    double obtenerPrecio() const override {
        return precioBase * (1 + impuesto);
    }
};

#endif
