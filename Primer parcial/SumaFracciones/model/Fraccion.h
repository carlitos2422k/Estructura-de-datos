#ifndef FRACCION_H
#define FRACCION_H

class Fraccion {
protected:
    int numerador;
    int denominador;

public:
    Fraccion(int numerador, int denominador) 
        : numerador(numerador), denominador(denominador) {}

    virtual int obtenerNumerador() const = 0;
    virtual int obtenerDenominador() const = 0;
};

class FraccionConcreta : public Fraccion {
public:
    FraccionConcreta(int numerador, int denominador)
        : Fraccion(numerador, denominador) {}

    int obtenerNumerador() const override {
        return numerador;
    }

    int obtenerDenominador() const override {
        return denominador;
    }
};

#endif
