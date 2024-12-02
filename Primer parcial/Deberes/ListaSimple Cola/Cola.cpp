#include "Cola.h"

template<typename T>
Cola<T>::Cola() {
    frente = nullptr;
    final = nullptr;
}

template<typename T>
Cola<T>::~Cola() {
    while (!estaVacia()) {
        Desencolar();
    }
}

template<typename T>
void Cola<T>::Encolar(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    if (estaVacia()) {
        frente = nuevo;
        final = nuevo;
    } else {
        final->setSiguiente(nuevo);
        final = nuevo;
    }
}

template<typename T>
void Cola<T>::Desencolar() {
    if (estaVacia()) {
        cout << "La cola está vacía, no se puede desencolar." << endl;
        return;
    }

    Nodo<T>* temp = frente;
    frente = frente->getSiguiente();
    delete temp;

    if (frente == nullptr) {
        final = nullptr;
    }
}

template<typename T>
void Cola<T>::Mostrar() {
    Nodo<T>* aux = frente;
    while (aux != nullptr) {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cedula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    }
}

template<typename T>
bool Cola<T>::estaVacia() {
    return frente == nullptr;
}
