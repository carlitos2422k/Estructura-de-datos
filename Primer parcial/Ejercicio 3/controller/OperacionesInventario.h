#ifndef OPERACIONESINVENTARIO_H
#define OPERACIONESINVENTARIO_H

#include "../model/Producto.h"
#include <vector>

class OperacionesInventario {
public:
    static double calcularPrecioTotal(const std::vector<Producto*>& productos) {
        double total = 0;
        for (const auto& producto : productos) {
            total += producto->obtenerPrecio();
        }
        return total;
    }
};

#endif
