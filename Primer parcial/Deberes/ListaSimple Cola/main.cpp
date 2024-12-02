#include "Cola.h"
#include "Nodo.cpp"
#include "utils.cpp"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "Validaciones.cpp"
#include <string>
using namespace std;

int main() {
    Cola<std::string>* cola = new Cola<std::string>();
    std::string Nombre, Apellido, Correo, cedulaStr;
    long int Cedula;
    Validaciones<std::string> ingresar_string;
    Validaciones<long> ingresar_entero;

    string opciones[] = { "Encolar", "Desencolar", "Mostrar", "Salir" };
    const int num_opciones = 4;
    int seleccion = 0;

    while (true) {
        Correo = "";
        Cedula = 0;
        cedulaStr = "";
        system("cls");
        cout << "*********** Colas ***********" << endl;

        // Mostrar opciones con un indicador para la opción seleccionada
        for (int i = 0; i < num_opciones; ++i) {
            if (i == seleccion)
                cout << "-> " << opciones[i] << endl;
            else
                cout << "   " << opciones[i] << endl;
        }

        // Capturar entrada del usuario
        char tecla = _getch();

        // Manejar teclas
        if (tecla == 72) { // Flecha arriba
            seleccion = (seleccion - 1 + num_opciones) % num_opciones;
        } else if (tecla == 80) { // Flecha abajo
            seleccion = (seleccion + 1) % num_opciones;
        } else if (tecla == 13) { // Enter
            // Ejecutar la opción seleccionada
            switch (seleccion) {
            case 0: // Encolar
                Nombre = ingresar_string.ingresar("Ingrese el nombre: ", "string");
                cout << endl;
                Apellido = ingresar_string.ingresar("Ingrese el apellido: ", "string");
                cout << endl;
                while (!Utils::validateEmail(Correo)) {
                    Correo = ingresar_string.ingresar("Ingrese el correo: ", "email");
                    cout << endl;
                    if (!Utils::validateEmail(Correo)) {
                        cout << "Correo invalido. Ingrese nuevamente." << endl;
                    }
                }
                while (!Utils::validateId(cedulaStr)) {
                    Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                    cout << endl;
                    cedulaStr = std::to_string(Cedula);

                    if (!Utils::validateId(cedulaStr)) {
                        cout << "Cedula invalida. Ingrese nuevamente." << endl;
                    }
                }
                cola->Encolar(Nombre, Apellido, cedulaStr, Correo);
                cout << endl << "Dato encolado correctamente." << endl;
                system("pause");
                break;

            case 1: // Desencolar
                cola->Desencolar();
                cout << "Primer nodo desencolado." << endl;
                system("pause");
                break;

            case 2: // Mostrar
                cola->Mostrar();
                cout << endl;
                system("pause");
                break;

            case 3: // Salir
                cout << "Saliendo del programa..." << endl;
                delete cola;
                return 0;

            default:
                break;
            }
        }
    }
}

