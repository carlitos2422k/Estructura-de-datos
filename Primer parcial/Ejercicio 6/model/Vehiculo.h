#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>
using namespace std;
class Vehiculo {
public:
    virtual ~Vehiculo() = default;
    virtual string getTipo() const = 0;
    virtual double getTarifa() const = 0;
};

#endif
