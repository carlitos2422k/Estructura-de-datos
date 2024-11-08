#ifndef CALIFICACIONTEORICA_H
#define CALIFICACIONTEORICA_H

#include "Calificacion.h"

class CalificacionTeorica : public Calificacion {
public:
    CalificacionTeorica(double nota1, double nota2) : Calificacion(nota1, nota2) {}

    double calcularNotaFinal() const override {
        return (nota1 + nota2) / 2.0;  // Promedio simple
    }
};

#endif
