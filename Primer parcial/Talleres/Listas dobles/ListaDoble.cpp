/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los m�todos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#include "ListaDoble.h"
#include <iostream>
using namespace std;

// Constructor
template<typename T>
ListaDoble<T>::ListaDoble() {
    primero = nullptr;
    ultimo = nullptr;
}

// Insertar al final
template<typename T>
void ListaDoble<T>::Insertar(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (primero == nullptr) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        ultimo = nuevo;
    }
}
// Insertar al inicio
template<typename T>
void ListaDoble<T>::InsertarCabeza(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (primero == nullptr) { // Si la lista está vacía
        primero = nuevo;
        ultimo = nuevo;
    } else {
        nuevo->setSiguiente(primero);  // El nuevo nodo apunta al primero actual
        primero->setAnterior(nuevo);  // El primero actual apunta de regreso al nuevo nodo
        primero = nuevo;              // Actualizamos el inicio de la lista
    }
}


// Buscar un dato
template<typename T>
void ListaDoble<T>::Buscar(T _dato) {
    Nodo<T>* aux = primero;
    while (aux != nullptr) {
        if (aux->getDato() == _dato) {
            cout << "El dato " << _dato << " se encuentra en la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

// Eliminar un nodo con el dato especificado
template<typename T>
void ListaDoble<T>::Eliminar(T _dato) {
    Nodo<T>* aux = primero;
    while (aux != nullptr) {
        if (aux->getDato() == _dato) {
            if (aux == primero) {
                primero = primero->getSiguiente();
                if (primero != nullptr) {
                    primero->setAnterior(nullptr);
                }
            } else if (aux == ultimo) {
                ultimo = ultimo->getAnterior();
                if (ultimo != nullptr) {
                    ultimo->setSiguiente(nullptr);
                }
            } else {
                aux->getAnterior()->setSiguiente(aux->getSiguiente());
                aux->getSiguiente()->setAnterior(aux->getAnterior());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

// Mostrar la lista
template<typename T>
void ListaDoble<T>::Mostrar() {
    Nodo<T>* aux = primero;
    while (aux != nullptr) {
        cout << aux->getDato() << " <-> ";
        aux = aux->getSiguiente();
    }
    cout << "NULL" << endl;
}

