#include <iostream>
#include "model/Auto.h"
#include "model/Camioneta.h"
#include "controller/AlquilerVehiculos.h"
using namespace std;
int main() {
    int opcion;
    int dias;

    cout << "Sistema de Alquiler de Vehículos\n";
    cout << "Seleccione el tipo de vehículo:\n";
    cout << "1. Auto\n";
    cout << "2. Camioneta\n";
    cout << "Opción: ";
    cin >> opcion;

    cout << "Ingrese el número de días de alquiler: ";
    cin >> dias;

    // Crear una instancia directa de cada clase en lugar de punteros
    Auto autoVehiculo;
    Camioneta camionetaVehiculo;
    AlquilerVehiculos alquiler;

    double total;
    if (opcion == 1) {
        total = alquiler.calcularTarifaTotal(autoVehiculo, dias);
        cout << "Tipo de vehículo: " << autoVehiculo.getTipo() << "\n";
    } else if (opcion == 2) {
        total = alquiler.calcularTarifaTotal(camionetaVehiculo, dias);
        cout << "Tipo de vehículo: " << camionetaVehiculo.getTipo() << "\n";
    } else {
        cout << "Opción inválida.\n";
        return 1;
    }

    cout << "Tarifa total por " << dias << " días: $" << total << "\n";

    return 0;
}
