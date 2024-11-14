#ifndef CAMIONETA_H
#define CAMIONETA_H

#include "Vehiculo.h"
using namespace std;
class Camioneta : public Vehiculo {
public:
    string getTipo() const override {
        return "Camioneta";
    }

    double getTarifa() const override {
        return 70.0; // Tarifa fija por día
    }
};

#endif
