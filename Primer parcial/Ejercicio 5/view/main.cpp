/*******************************************************
 * Universidad de las Fuerzas Armadas ESPE             *
 * Departamento de Ciencias de la Computación          *
 * Autor: Carlos Pérez                                 *
 * Fecha: Lunes 4 de noviembre del 2024                *
 *******************************************************/
#include <iostream>
#include "../model/Auto.h"
#include "../model/Moto.h"
#include "../controller/OperacionesEstacionamiento.h"
using namespace std;
int main() {
    string PlacaAuto, PlacaMoto;
    string ModeloAuto, ModeloMoto;

    Auto auto1(PlacaAuto, ModeloAuto);
    Moto moto1(PlacaMoto, ModeloMoto);
    int horasAuto; 
    int horasMoto; 
    cout << "Horas de estacionamiento del Auto: ";
    cin >> horasAuto;
    cout << "Horas de estacionamiento de la Moto: ";
    cin >> horasMoto;
    double costoAuto = OperacionesEstacionamiento::calcularCosto(auto1, horasAuto);
    double costoMoto = OperacionesEstacionamiento::calcularCosto(moto1, horasMoto);

    cout << "Costo de estacionamiento para el auto: $" << costoAuto << endl;
    cout << "Costo de estacionamiento para la moto: $" << costoMoto << endl;

    return 0;
}
