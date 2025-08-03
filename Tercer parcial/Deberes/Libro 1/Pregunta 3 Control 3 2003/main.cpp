#include <iostream>
#include "V.h"

int main() {
    // Crear un arreglo de valores con muchos ceros
    double valores[] = {0, 2.5, 0, 3.1, 0, 4.2};
    int size = sizeof(valores) / sizeof(valores[0]);

    // Crear el objeto V con los valores
    V d(valores, size);

    // Crear otro arreglo para el vector e
    double valores2[] = {1.1, 0, 3.2, 0, 5.0};
    V e(valores2, sizeof(valores2) / sizeof(valores2[0]));

    // Realizar el producto punto entre los dos vectores
    double productoPunto = d.pPunto(e);
    std::cout << "El producto punto es: " << productoPunto << std::endl;

    // Proyectar el vector d eliminando el índice 3
    d.proyectar(3);
    std::cout << "Se ha proyectado el vector d eliminando el índice 3." << std::endl;

    return 0;
}
