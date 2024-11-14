#include <iostream>
#include "model/Dolar.h"
#include "model/Euro.h"
#include "controller/ConvertidorMoneda.h"
using namespace std;
int main() {
    int opcion;
    double cantidad, resultado;

    cout << "Sistema de Conversión de Monedas\n";
    cout << "Ingrese la cantidad en dólares: ";
    cin >> cantidad;

    cout << "Seleccione la moneda a la que desea convertir:\n";
    cout << "1. Dólar\n";
    cout << "2. Euro\n";
    cout << "Opción: ";
    cin >> opcion;

    ConvertidorMoneda convertidor;

    if (opcion == 1) {
        Dolar dolar;
        resultado = convertidor.convertir(dolar, cantidad);
        cout << "Cantidad en dólares: " << resultado << "\n";
    } 
    else if (opcion == 2) {
        Euro euro;
        resultado = convertidor.convertir(euro, cantidad);
        cout << "Cantidad en euros: " << resultado << "\n";
    } 
    else {
        cout << "Opción inválida.\n";
        return 1;
    }

    return 0;
}
