#ifndef OPERACIONESPERIMETRO_H
#define OPERACIONESPERIMETRO_H

#include "../model/Figura.h"
#include "../model/Rectangulo.h"
#include "../model/Circulo.h"

class OperacionesPerimetro {
public:
    static double calcularPerimetroFigura(Figura* figura) {
        return figura->calcularPerimetro();
    }
};

#endif
