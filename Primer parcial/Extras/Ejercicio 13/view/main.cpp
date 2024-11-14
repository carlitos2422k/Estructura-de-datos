#include <iostream>
#include "model/ProductoConcreto.h"
#include "controller/CalculoPrecio.h"

int main() {
    double precioBase;
    CalculoPrecio calculo;

    std::cout << "Ingrese el precio base del producto: ";
    std::cin >> precioBase;

    ProductoConcreto producto(precioBase);
    std::cout << "El precio total del producto con el 12% de impuesto es: $" 
              << calculo.mostrarPrecioFinal(producto) << std::endl;

    return 0;
}
