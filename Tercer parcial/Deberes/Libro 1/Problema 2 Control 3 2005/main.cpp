#include <iostream>
#include "Tabla.h"

int main() {
    // Crear la tabla
    Tabla t = Tabla::crearTabla();

    // Mostrar algunos valores para verificar la tabla
    std::cout << "Valor en (1, 2): " << t.getValor(1, 2) << std::endl;
    std::cout << "Valor en (1, 21): " << t.getValor(1, 21) << std::endl;
    std::cout << "Valor en (2, 1): " << t.getValor(2, 1) << std::endl;

    return 0;
}
