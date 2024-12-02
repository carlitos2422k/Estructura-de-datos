#include "Pila.h"

template<typename T>
Pila<T>::Pila() {
    cima = nullptr;
}

template<typename T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        Desapilar();
    }
}

template<typename T>
void Pila<T>::Apilar(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    nuevo->setSiguiente(cima);
    cima = nuevo;
}

template<typename T>
void Pila<T>::Desapilar() {
    if (estaVacia()) {
        cout << "La pila está vacía, no se puede desapilar." << endl;
        return;
    }

    Nodo<T>* temp = cima;
    cima = cima->getSiguiente();
    delete temp;
}

template<typename T>
void Pila<T>::Mostrar() {
    Nodo<T>* aux = cima;
    while (aux != nullptr) {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cedula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    }
}

template<typename T>
bool Pila<T>::estaVacia() {
    return cima == nullptr;
}
