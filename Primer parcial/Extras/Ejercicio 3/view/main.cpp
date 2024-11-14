/*******************************************************
 * Universidad de las Fuerzas Armadas ESPE             *
 * Departamento de Ciencias de la Computación          *
 * Autor: Carlos Pérez                                 *
 * Fecha: Sabado 2 de noviembre del 2024               *
 *******************************************************/
#include <iostream>
#include <vector>
#include "../controller/OperacionesInventario.h"
#include "../model/ProductoAlimento.h"
#include "../model/ProductoElectronico.h"
using namespace std;
int main() {
    double PrecioManzana;
    double PrecioTV;
    cout << "Ingrese el precio de la manzana: ";
    cin >> PrecioManzana;
    cout << "Ingrese el precio de la TV: ";
    cin >> PrecioTV;
    ProductoAlimento manzana(PrecioManzana); 
    ProductoElectronico televisor( PrecioTV, 0.15); 

    vector<Producto*> inventario = { &manzana, &televisor };

    double precioTotal = OperacionesInventario::calcularPrecioTotal(inventario);

    cout << "Precio total del inventario: $" << precioTotal << endl;

    return 0;
}
