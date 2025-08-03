#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "F.h"

class FuncionF : public F {
public:
    double valor(double x) override {
        // Implementación de f(x), por ejemplo: f(x) = x^2
        return x * x;
    }
};

class FuncionG : public F {
public:
    double valor(double x) override {
        // Implementación de g(x), por ejemplo: g(x) = x
        return x;
    }
};

#endif
