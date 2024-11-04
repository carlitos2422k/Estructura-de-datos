#ifndef PRODUCTO_H
#define PRODUCTO_H

class Producto {
public:
    virtual double obtenerPrecio() const = 0;
    virtual ~Producto() {} 
};

#endif
