#include "ListaDoble.h"

template<typename T>
ListaDoble<T>::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
}

template<typename T>
void ListaDoble<T>::InsertarPorCabeza(T nombre, T apellido, T cedula, T correo) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
        cabeza = nuevo;
    }
}

template<typename T>
void ListaDoble<T>::InsertarPorCola(T nombre, T apellido, T cedula, T correo) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(nombre, apellido, cedula, correo);
    if (cola == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
}

template<typename T>
void ListaDoble<T>::Mostrar() {
    NodoDoble<T>* aux = cabeza;
    while (aux != nullptr) {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cedula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    }
}

template<typename T>
void ListaDoble<T>::BuscarPorCedula(T cedula) {
    NodoDoble<T>* aux = cabeza;
    while (aux != nullptr) {
        if (aux->getCedula() == cedula) {
            cout << "Registro encontrado: " << endl;
            cout << "Nombre: " << aux->getNombre()
                 << ", Apellido: " << aux->getApellido()
                 << ", Cédula: " << aux->getCedula()
                 << ", Correo: " << aux->getCorreo() << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}
