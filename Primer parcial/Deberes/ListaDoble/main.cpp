#include "ListaDoble.cpp"
#include "NodoDoble.cpp"
#include "utils.cpp"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "Validaciones.cpp"
#include <string>
using namespace std;

int main() {
    ListaDoble<std::string>* lista_string1 = new ListaDoble<std::string>();
    std::string Nombre, Apellido, Correo, cedulaStr;
    long int Cedula;
    int opcion;
    Validaciones<std::string> ingresar_string;
    Validaciones<long> ingresar_entero;
    Validaciones<int> ingresar_entero1;

    string opciones[] = { "Insertar por cabeza", "Insertar por cola" ,"Buscar por cedula", "Eliminar Nodo", "Eliminar datos de nodo", "Mostrar", "Salir" };
    const int num_opciones = 7;
    int seleccion = 0;
        while (true) {
        Correo = "";
        cedulaStr = "";
        
        system("cls");
        cout << "*********** Listas Dobles ***********" << endl;

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
            case 0: // Insertar
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
                lista_string1->InsertarPorCabeza(Nombre, Apellido, cedulaStr, Correo);
                cout << endl << "Dato ingresado correctamente." << endl;
                system("pause");
                break;
            case 1: // Insertar
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
                lista_string1->InsertarPorCola(Nombre, Apellido, cedulaStr, Correo);
                cout << endl << "Dato ingresado correctamente." << endl;
                system("pause");
                break;

            case 2: // Buscar por cedula
                Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                cout << endl;
                cedulaStr = std::to_string(Cedula);
                lista_string1->BuscarPorCedula(cedulaStr);
                system("pause");
                break;

            case 3: // Eliminar Nodo
                while (!Utils::validateId(cedulaStr)) {
                    Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                    cout << endl;
                    cedulaStr = std::to_string(Cedula);

                    if (!Utils::validateId(cedulaStr)) {
                        cout << "Cedula invalida. Ingrese nuevamente." << endl;
                    }
                }
                lista_string1->EliminarNodoPorCedula(cedulaStr);
                break;
            case 4: // Eliminar Datos
                while (!Utils::validateId(cedulaStr)) {
                    Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                    cout << endl;
                    cedulaStr = std::to_string(Cedula);

                    if (!Utils::validateId(cedulaStr)) {
                        cout << "Cedula invalida. Ingrese nuevamente." << endl;
                    }
                }
                lista_string1->EliminarDatosNodoPorCedula(cedulaStr);
                break;
            case 5: // Mostrar
                lista_string1->Mostrar();
                cout << endl;
                system("pause");
                break;

            case 6: // Salir
                cout << "Saliendo del programa..." << endl;
                delete lista_string1;
                return 0;

            default:
                break;
            }
        }
    }
}
