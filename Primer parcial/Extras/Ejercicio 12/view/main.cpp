#include <iostream>
#include "model/Carro.h"
#include "model/Bicicleta.h"
#include "controller/CalculoDistancia.h"

int main() {
    int opcion;
    double tiempo;
    CalculoDistancia calculo;

    std::cout << "Seleccione el tipo de vehículo:\n";
    std::cout << "1. Carro\n";
    std::cout << "2. Bicicleta\n";
    std::cout << "Opción: ";
    std::cin >> opcion;

    std::cout << "Ingrese el tiempo en horas: ";
    std::cin >> tiempo;

    if (opcion == 1) {
        double velocidad;
        std::cout << "Ingrese la velocidad del carro en km/h: ";
        std::cin >> velocidad;

        Carro carro(velocidad);
        std::cout << "La distancia recorrida por el carro es: " << calculo.mostrarDistancia(carro, tiempo) << " km\n";
    } else if (opcion == 2) {
        double velocidad;
        std::cout << "Ingrese la velocidad de la bicicleta en km/h: ";
        std::cin >> velocidad;

        Bicicleta bicicleta(velocidad);
        std::cout << "La distancia recorrida por la bicicleta es: " << calculo.mostrarDistancia(bicicleta, tiempo) << " km\n";
    } else {
        std::cout << "Opción no válida.\n";
    }

    return 0;
}
