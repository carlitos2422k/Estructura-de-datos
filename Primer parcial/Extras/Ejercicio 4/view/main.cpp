/*******************************************************
 * Universidad de las Fuerzas Armadas ESPE             *
 * Departamento de Ciencias de la Computación          *
 * Autor: Carlos Pérez                                 *
 * Fecha: Domingo 3 de noviembre del 2024              *
 *******************************************************/
#include <iostream>
#include <vector>
#include "../controller/OperacionesEmpleados.h"
#include "../model/EmpleadoTiempoCompleto.h"
#include "../model/EmpleadoTiempoParcial.h"
using namespace std;
int main() {
    string NombreEmpleadoTC, NombreEmpleadoTP;
    double SalarioMensual, HorasTrabajo;
    cout << "Ingrese el nombre del empleado tiempo completo: ";
    cin >> NombreEmpleadoTC;
    cout <<" Ingrese su salario mensual: ";
    cin >> SalarioMensual;
        cout << "Ingrese el nombre del empleado tiempo parcial: ";
    cin >> NombreEmpleadoTP;
    cout <<" Ingrese las horas trabajadas: ";
    cin >> HorasTrabajo;
    EmpleadoTiempoCompleto empleado1(NombreEmpleadoTC, SalarioMensual); 
    EmpleadoTiempoParcial empleado2(NombreEmpleadoTC, 15, HorasTrabajo); 

    vector<Empleado*> empleados = { &empleado1, &empleado2 };

    double salarioTotal = OperacionesEmpleados::calcularSalarioTotal(empleados);

    cout << "Salario total de los empleados: $" << salarioTotal << endl;

    return 0;
}
