#include "Lista_Simple.cpp"
#include "Nodo.cpp"
#include "utils.cpp"
#include <iostream>
#include <conio.h> 
#include <stdlib.h>
#include "Validaciones.cpp"
#include <string>
using namespace std;

int main() {
    Lista_Simple<std::string>* lista_string1 = new Lista_Simple<std::string>();
    std::string Nombre, Apellido, Correo, cedulaStr;
    long int Cedula;
    Validaciones<std::string> ingresar_string;
    Validaciones<long> ingresar_entero;
    Validaciones<int> ingresar_entero1;

    string opciones[] = { "Insertar", "Buscar por cedula", "Eliminar Nodo", "Eliminar Datos", "Mostrar", "Salir" };
    const int num_opciones = 6;
    int seleccion = 0;

    while (true) {
        Correo="";
        Cedula=0;
        cedulaStr="";
        system("cls");
        cout << "*********** Listas Simples ***********" << endl;

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
                lista_string1->Insertar(Nombre, Apellido, cedulaStr, Correo);
                cout << endl << "Dato ingresado correctamente." << endl;
                system("pause");
                break;

            case 1: // Buscar por cedula
                while (!Utils::validateId(cedulaStr)) {
                    Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                    cout << endl;
                    cedulaStr = std::to_string(Cedula);

                    if (!Utils::validateId(cedulaStr)) {
                        cout << "Cedula invalida. Ingrese nuevamente." << endl;
                    }
                }
                lista_string1->BuscarPorCedula(cedulaStr);
                system("pause");
                break;

            case 2: // Eliminar Nodo
                while (!Utils::validateId(cedulaStr)) {
                    Cedula = ingresar_entero.ingresar("Ingrese la cedula que contiene el Nodo a eliminar: ", "long");
                    cout << endl;
                    cedulaStr = std::to_string(Cedula);

                    if (!Utils::validateId(cedulaStr)) {
                        cout << "Cedula invalida. Ingrese nuevamente." << endl;
                    }
                }
                lista_string1->EliminarNodoPorCedula(cedulaStr);
                cout << "Nodo eliminado";
                system("pause");
                break;
            case 3: // Eliminar Datos
                while (!Utils::validateId(cedulaStr)) {
                    Cedula = ingresar_entero.ingresar("Ingrese la cedula que contiene los datos a eliminar: ", "long");
                    cout << endl;
                    cedulaStr = std::to_string(Cedula);

                    if (!Utils::validateId(cedulaStr)) {
                        cout << "Cedula invalida. Ingrese nuevamente." << endl;
                    }
                }
                lista_string1->LimpiarDatosNodo(cedulaStr);
                cout << "Datos eliminados ";
                system("pause");
                break;
            case 4: // Mostrar
                lista_string1->Mostrar();
                cout << endl;
                system("pause");
                break;

            case 5: // Salir
                cout << "Saliendo del programa..." << endl;
                delete lista_string1;
                return 0;

            default:
                break;
            }
        }
    }
}
