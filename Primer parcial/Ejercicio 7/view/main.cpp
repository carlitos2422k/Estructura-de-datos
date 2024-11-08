#include <iostream>
#include "model/Cubo.h"
#include "model/Esfera.h"
#include "controller/CalculoVolumen.h"
using namespace std;
int main() {
    int opcion;
    double volumen;

    cout << "Sistema de Cálculo de Volumen de Sólidos\n";
    cout << "Seleccione el sólido geométrico:\n";
    cout << "1. Cubo\n";
    cout << "2. Esfera\n";
    cout << "Opción: ";
    cin >> opcion;

    CalculoVolumen calculo;

    if (opcion == 1) {
        double lado;
        cout << "Ingrese el lado del cubo: ";
        cin >> lado;

        Cubo cubo(lado);
        volumen = calculo.calcularVolumenSolido(cubo);
        cout << "Volumen del cubo: " << volumen << "\n";
    } 
    else if (opcion == 2) {
        double radio;
        cout << "Ingrese el radio de la esfera: ";
        cin >> radio;

        Esfera esfera(radio);
        volumen = calculo.calcularVolumenSolido(esfera);
        cout << "Volumen de la esfera: " << volumen << "\n";
    } 
    else {
        cout << "Opción inválida.\n";
        return 1;
    }

    return 0;
}
