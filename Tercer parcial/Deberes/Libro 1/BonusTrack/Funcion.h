#ifndef FUNCION_H
#define FUNCION_H

class Funcion {
public:
    virtual double valor(double x) const = 0;  // Método virtual puro
    virtual ~Funcion() {}
};

#endif
