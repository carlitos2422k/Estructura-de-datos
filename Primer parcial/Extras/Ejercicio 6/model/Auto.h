#ifndef AUTO_H
#define AUTO_H

#include "Vehiculo.h"
using namespace std;
class Auto : public Vehiculo {
public:
    string getTipo() const override {
        return "Auto";
    }

    double getTarifa() const override {
        return 50.0; // Tarifa fija por día
    }
};

#endif
