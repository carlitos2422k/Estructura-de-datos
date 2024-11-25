#include "Lista_Simple.h"

template<typename T>
Lista_Simple<T>::Lista_Simple() {
    cabeza = nullptr;
}

template<typename T>
void Lista_Simple<T>::Insertar(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != nullptr) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

template<typename T>
void Lista_Simple<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    while (aux != nullptr) {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cedula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    }
}

template<typename T>
void Lista_Simple<T>::BuscarPorCedula(T cedula) {
    Nodo<T>* aux = cabeza;
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
