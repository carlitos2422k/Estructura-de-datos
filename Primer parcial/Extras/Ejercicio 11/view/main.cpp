#include <iostream>
#include "model/Carro.h"
#include "model/Moto.h"
#include "controller/CalculoVelocidad.h"

int main() {
    int opcion;
    CalculoVelocidad calculo;

    std::cout << "Seleccione el tipo de vehículo:\n";
    std::cout << "1. Carro\n";
    std::cout << "2. Moto\n";
    std::cout << "Opción: ";
    std::cin >> opcion;

    if (opcion == 1) {
        int velocidad;
        std::cout << "Ingrese la velocidad máxima del carro: ";
        std::cin >> velocidad;

        Carro carro(velocidad);
        std::cout << "La velocidad máxima del carro es: " << calculo.mostrarVelocidad(carro) << " km/h\n";
    } else if (opcion == 2) {
        int velocidad;
        std::cout << "Ingrese la velocidad máxima de la moto: ";
        std::cin >> velocidad;

        Moto moto(velocidad);
        std::cout << "La velocidad máxima de la moto es: " << calculo.mostrarVelocidad(moto) << " km/h\n";
    } else {
        std::cout << "Opción no válida.\n";
    }

    return 0;
}
