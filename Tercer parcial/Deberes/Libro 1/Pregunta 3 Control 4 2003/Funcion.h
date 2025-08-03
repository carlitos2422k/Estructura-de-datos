#ifndef FUNCION_H
#define FUNCION_H

// Clase abstracta que representa una función continua
class Funcion {
public:
    virtual double evaluar(double x) const = 0;  // Método abstracto para evaluar la función
    virtual ~Funcion() = default;  // Destructor virtual para permitir la herencia adecuada
};

#endif
