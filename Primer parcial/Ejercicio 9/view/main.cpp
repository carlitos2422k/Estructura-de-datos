#include <iostream>
#include "model/CalificacionTeorica.h"
#include "model/CalificacionPractica.h"
#include "controller/CalculoNota.h"
using namespace std;
int main() {
    int tipoCalificacion;
    double nota1, nota2;

    cout << "Sistema de Calificaciones\n";
    cout << "Ingrese la primera nota: ";
    cin >> nota1;
    cout << "Ingrese la segunda nota: ";
    cin >> nota2;

    cout << "Seleccione el tipo de calificación:\n";
    cout << "1. Teórica\n";
    cout << "2. Práctica\n";
    cout << "Opción: ";
    cin >> tipoCalificacion;

    CalculoNota calculo;

    if (tipoCalificacion == 1) {
        CalificacionTeorica teorica(nota1, nota2);
        cout << "Nota final teórica: " << calculo.calcular(teorica) << "\n";
    } 
    else if (tipoCalificacion == 2) {
        CalificacionPractica practica(nota1, nota2);
        cout << "Nota final práctica: " << calculo.calcular(practica) << "\n";
    } 
    else {
        cout << "Opción inválida.\n";
        return 1;
    }

    return 0;
}
