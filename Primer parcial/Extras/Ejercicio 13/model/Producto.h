#ifndef PRODUCTO_H
#define PRODUCTO_H

class Producto {
protected:
    double precioBase;

public:
    Producto(double precioBase) : precioBase(precioBase) {}
    virtual ~Producto() = default;
    virtual double calcularPrecioConImpuesto() const = 0;
};

#endif
