#ifndef OPERACIONESFIGURA_H
#define OPERACIONESFIGURA_H

#include "../model/FiguraGeometrica.h"
#include "../model/Cuadrado.h"
#include "../model/Triangulo.h"

class OperacionesFigura {
public:
    static double calcularAreaFigura(FiguraGeometrica* figura) {
        return figura->calcularArea();
    }
};

#endif
