#ifndef ISUMAFRACCION_H
#define ISUMAFRACCION_H

template <typename T>
class ISumaFraccion {
public:
    virtual T sumar(const T& fraccion1, const T& fraccion2) = 0; // Método para sumar fracciones
};

#endif

