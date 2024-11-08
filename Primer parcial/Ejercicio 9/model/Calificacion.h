#ifndef CALIFICACION_H
#define CALIFICACION_H

class Calificacion {
protected:
    double nota1, nota2;

public:
    Calificacion(double nota1, double nota2) : nota1(nota1), nota2(nota2) {}

    virtual ~Calificacion() = default;

    virtual double calcularNotaFinal() const = 0;
};

#endif


