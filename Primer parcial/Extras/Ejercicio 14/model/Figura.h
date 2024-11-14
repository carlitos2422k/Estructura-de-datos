#ifndef FIGURA_H
#define FIGURA_H

class Figura {
public:
    virtual ~Figura() = default;
    virtual double calcularArea() const = 0;
    virtual double calcularPerimetro() const = 0;
};

#endif
