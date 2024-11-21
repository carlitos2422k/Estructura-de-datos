#include <iostream>
#include "ListaEnlazada.h"

using namespace std;

int main() {
    ListaEnlazada<int> listaEnteros;
    int seleccion, value;

    while (true) {
        cout << "\n--- Menú de Operaciones ---\n";
        cout << "1. Insertar elemento al inicio\n";
        cout << "2. Insertar elemento al final\n";
        cout << "3. Mostrar lista\n";
        cout << "4. Buscar un elemento\n";
        cout << "5. Eliminar un elemento por valor\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> seleccion;

        switch (seleccion) {
            case 1: // Insertar al inicio
                cout << "Ingrese el valor a insertar al inicio: ";
                cin >> value;
                listaEnteros.insertarPorCabeza(value);
                cout << "Elemento insertado.\n";
                break;

            case 2: // Insertar al final
                cout << "Ingrese el valor a insertar al final: ";
                cin >> value;
                listaEnteros.insertarPorCola(value);
                cout << "Elemento insertado.\n";
                break;

            case 3: // Mostrar lista
                cout << "Lista actual: ";
                listaEnteros.mostrarLista();
                break;

            case 4: { // Buscar un elemento
                cout << "Ingrese el valor a buscar: ";
                cin >> value;
                int indice = listaEnteros.buscarElemento([value](const int& dato) {
                    return dato == value;
                });
                if (indice != -1) {
                    cout << "Elemento " << value << " encontrado en el índice: " << indice << ".\n";
                } else {
                    cout << "Elemento " << value << " no encontrado.\n";
                }
                break;
            }

            case 5: { // Eliminar un elemento por valor
                cout << "Ingrese el valor a eliminar: ";
                cin >> value;
                listaEnteros.eliminarElemento([value](const int& dato) {
                    return dato == value;
                });
                cout << "Elemento eliminado si existía.\n";
                break;
            }

            case 6: // Salir
                cout << "Saliendo del programa. Liberando memoria...\n";
                return 0;

            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }

        cout << "Lista actualizada: ";
        listaEnteros.mostrarLista();
    }
}
