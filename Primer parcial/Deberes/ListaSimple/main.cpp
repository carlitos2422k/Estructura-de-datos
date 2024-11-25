#include "Lista_Simple.cpp"
#include "Nodo.cpp"
#include "utils.cpp"
#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
#include <string>
using namespace std;

int main() {
    Lista_Simple<std::string>* lista_string1 = new Lista_Simple<std::string>();
    std::string Nombre, Apellido, Correo, cedulaStr;
    long int Cedula;
    int opcion;
    Validaciones<std::string> ingresar_string;
    Validaciones<long> ingresar_entero;
    Validaciones<int> ingresar_entero1;

    do {
        system("cls");  // Limpiar pantalla en cada iteración para mantener la interfaz limpia
        cout << "*********** Listas Simples ***********" << endl;
        cout << "1. Insertar" << endl;
        cout << "2. Buscar por cedula" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Mostrar" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        opcion = ingresar_entero1.ingresar("Opcion: ", "entero");
        cout << endl;

        switch (opcion) {
        case 1:
            Nombre = ingresar_string.ingresar("Ingrese el nombre: ", "string");
            cout << endl;
            Apellido = ingresar_string.ingresar("Ingrese el apellido: ", "string");
            cout << endl;
            while (!Utils::validateEmail(Correo))
            {
                Correo = ingresar_string.ingresar("Ingrese el correo: ", "email");
                cout << endl;
                    if (!Utils::validateEmail(Correo)) {
                    cout << "Corrreo invalido.";
                    cout << endl;
                    cout <<"Ingrese nuevamente";
                    cout << endl;
                }
            }
            while (!Utils::validateId(cedulaStr)){
                Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
                cout << endl;
                cedulaStr = std::to_string(Cedula);

                if (!Utils::validateId(cedulaStr)) {
                    cout << "Cedula invalida.";
                    cout << endl;
                    cout <<"Ingrese nuevamente";
                    cout << endl;
                }
            }
            lista_string1->Insertar(Nombre, Apellido, cedulaStr, Correo);
            cout << endl << "Dato ingresado correctamente." << endl;
            system("pause");  
            break;
        case 2:
            Cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "long");
            cout << endl;
            cedulaStr = std::to_string(Cedula);
            lista_string1->BuscarPorCedula(cedulaStr);
            system("pause");  
            break;
        case 3:
            
            cout << "Eliminar función aún no implementada." << endl;
            system("pause");  
            break;
        case 4:
            
            lista_string1->Mostrar();
            cout << endl;
            system("pause");  
            break;
        case 5:
            
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida, intente de nuevo." << endl;
            system("pause");  
            break;
        }
    } while (opcion != 5);  

    delete lista_string1;  
    return 0;
}
