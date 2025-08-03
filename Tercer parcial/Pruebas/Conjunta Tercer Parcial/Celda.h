#ifndef CELDA_H
#define CELDA_H

#include "Punto.h"

class Celda {
private:
    char letra;
    Punto posicion;
    
public:
    Celda(char l = ' ', const Punto& pos = Punto());
    
    char obtenerLetra() const;
    Punto obtenerPosicion() const;
    void establecerLetra(char l);
    void establecerPosicion(const Punto& pos);
};

#endif // CELDA_H