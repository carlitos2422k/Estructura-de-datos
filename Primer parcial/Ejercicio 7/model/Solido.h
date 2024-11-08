#ifndef SOLIDO_H
#define SOLIDO_H

class Solido {
public:
    virtual ~Solido() = default;
    virtual double calcularVolumen() const = 0;
};

#endif
