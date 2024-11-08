#ifndef MONEDA_H
#define MONEDA_H

class Moneda {
public:
    virtual ~Moneda() = default;
    virtual double convertirA(double cantidad) const = 0;
};

#endif
