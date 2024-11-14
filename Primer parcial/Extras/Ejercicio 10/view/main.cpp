#include <iostream>
#include "model/EmpleadoPermanente.h"
#include "model/EmpleadoTemporal.h"
#include "controller/CalculoBono.h"

using namespace std;
int main() {
    int tipoEmpleado;
    double salarioBase;

    cout << "Sistema de Bonos de Empleados\n";
    cout << "Ingrese el salario base del empleado: ";
    cin >> salarioBase;

    cout << "Seleccione el tipo de empleado:\n";
    cout << "1. Permanente\n";
    cout << "Opción: ";
    cin >> tipoEmpleado;

    CalculoBono calculo;

    if (tipoEmpleado == 1) {
        EmpleadoPermanente permanente(salarioBase);
        cout << "Bono para empleado permanente: $" << calculo.calcular(permanente) << "\n";
    } 
    else if (tipoEmpleado == 2) {
        EmpleadoTemporal temporal(salarioBase);
        cout << "Bono para empleado temporal: $" << calculo.calcular(temporal) << "\n";
    } 
    else {
        cout << "Opción inválida.\n";
        return 1;
    }

    return 0;
}
