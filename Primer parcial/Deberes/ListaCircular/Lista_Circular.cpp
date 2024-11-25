#include "Lista_Circular.h"

template<typename T>
Lista_Circular<T>::Lista_Circular() {
    cabeza = nullptr;
}

template<typename T>
void Lista_Circular<T>::InsertarPorCabeza(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        nuevo->setSiguiente(cabeza);  // Apuntamos a sí mismo
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != cabeza) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;  // Actualizamos la cabeza
    }
}

template<typename T>
void Lista_Circular<T>::InsertarPorCola(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        nuevo->setSiguiente(cabeza);  // Apuntamos a sí mismo
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != cabeza) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza);
    }
}

template<typename T>
void Lista_Circular<T>::Mostrar() {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* aux = cabeza;
    do {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cédula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    } while (aux != cabeza);
}

template<typename T>
void Lista_Circular<T>::BuscarPorCedula(T cedula) {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* aux = cabeza;
    do {
        if (aux->getCedula() == cedula) {
            cout << "Registro encontrado: " << endl;
            cout << "Nombre: " << aux->getNombre()
                 << ", Apellido: " << aux->getApellido()
                 << ", Cédula: " << aux->getCedula()
                 << ", Correo: " << aux->getCorreo() << endl;
            return;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}
