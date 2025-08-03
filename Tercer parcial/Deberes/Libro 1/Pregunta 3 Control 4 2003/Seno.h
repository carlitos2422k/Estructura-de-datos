#ifndef SENO_H
#define SENO_H
#include "Funcion.h"
#include <cmath>

// Clase que implementa la función seno
class Seno : public Funcion {
public:
    double evaluar(double x) const override {
        return std::sin(x);  // Devuelve el valor de seno de x
    }
};

#endif
