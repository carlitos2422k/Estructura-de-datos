#ifndef CALIFICACIONPRACTICA_H
#define CALIFICACIONPRACTICA_H

#include "Calificacion.h"

class CalificacionPractica : public Calificacion {
public:
    CalificacionPractica(double nota1, double nota2) : Calificacion(nota1, nota2) {}

    double calcularNotaFinal() const override {
        return (nota1 * 0.4 + nota2 * 0.6);  // Ponderación: 40% y 60%
    }
};

#endif
