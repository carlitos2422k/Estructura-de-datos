#include "ListaDoble.cpp"
#include "NodoDoble.cpp"
#include "utils.cpp"
#include <iostream>
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

    do {
        
        system("cls");
        cout << "*********** Listas Dobles ***********" << endl;
        cout << "1. Insertar por cabeza" << endl;
        cout << "2. Insertar por cola" << endl;
        cout << "3. Buscar por cedula" << endl;
        cout << "4. Eliminar (sin implementar)" << endl;
        cout << "5. Mostrar" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        opcion = ingresar_entero1.ingresar("Opcion: ", "entero");
        cout << endl;
        Correo="";
        cedulaStr="";
        switch (opcion) {
        case 1:
            

            Nombre = ingresar_string.ingresar("Ingrese el nombre: ", "string");
            cout << endl;
            Apellido = ingresar_string.ingresar("Ingrese el apellido: ", "string");
            cout << endl;
            while (!Utils::validateEmail(Correo)) {
                Correo = ingresar_string.ingresar("Ingrese el correo: ", "email");
                cout << endl;
                if (!Utils::validateEmail(Correo)) {
                    cout << "Correo invalido. Ingrese nuevamente.";
                    cout << endl;
                }
            }
            while (!Utils::validateId(cedulaStr)) {
                Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                cedulaStr = std::to_string(Cedula);
                if (!Utils::validateId(cedulaStr)) {
                    cout << "Cedula invalida. Ingrese nuevamente." << endl;
                    cout << endl;
                }
            }
            lista_string1->InsertarPorCabeza(Nombre, Apellido, cedulaStr, Correo);
            cout << "Dato ingresado correctamente.";
            cout << endl;
            system("pause");
            break;

        case 2:
            Nombre = ingresar_string.ingresar("Ingrese el nombre: ", "string");
            cout << endl;
            Apellido = ingresar_string.ingresar("Ingrese el apellido: ", "string");
            cout << endl;
            while (!Utils::validateEmail(Correo)) {
                Correo = ingresar_string.ingresar("Ingrese el correo: ", "email");
                cout << endl;
                if (!Utils::validateEmail(Correo)) {
                    cout << "Correo invalido. Ingrese nuevamente.";
                    cout << endl;
                }
            }
            while (!Utils::validateId(cedulaStr)) {
                Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                cedulaStr = std::to_string(Cedula);
                if (!Utils::validateId(cedulaStr)) {
                    cout << "Cedula invalida. Ingrese nuevamente.";
                    cout << endl;
                }
            }
            lista_string1->InsertarPorCola(Nombre, Apellido, cedulaStr, Correo);
            cout << "Dato ingresado correctamente.";
            cout << endl;
            system("pause");
            break;
        case 3:
            Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
            cedulaStr = std::to_string(Cedula);
            lista_string1->BuscarPorCedula(cedulaStr);
            system("pause");
            break;
        case 4:
            cout << "Eliminar función aún no implementada." << endl;
            system("pause");
            break;
        case 5:
            lista_string1->Mostrar();
            system("pause");
            break;
        case 6:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida, intente de nuevo." << endl;
            system("pause");
            break;
        }
    } while (opcion != 6);

    delete lista_string1;
    return 0;
}
