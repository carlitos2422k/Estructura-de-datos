#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

    void mostrarListaRecursivo(Nodo<T>* nodo) const {
        if (nodo == nullptr) {
            std::cout << "nullptr" << std::endl;
            return;
        }
        std::cout << nodo->dato << " -> ";
        mostrarListaRecursivo(nodo->siguiente);
    }

    int buscarElementoRecursivo(Nodo<T>* nodo, std::function<bool(const T&)> condicion, int indice) const {
        if (!nodo) return -1; // Caso base: no encontrado
        if (condicion(nodo->dato)) return indice; // Elemento encontrado
        return buscarElementoRecursivo(nodo->siguiente, condicion, indice + 1);
    }

    void eliminarNodoEnIndice(int indice) {
        if (!cabeza) return; // Lista vacía

        if (indice == 0) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            if (cabeza == nullptr) cola = nullptr; // Si la lista queda vacía
            delete temp;
            return;
        }

        Nodo<T>* actual = cabeza;
        for (int i = 0; actual && i < indice - 1; ++i) {
            actual = actual->siguiente;
        }

        if (actual && actual->siguiente) {
            Nodo<T>* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            if (temp == cola) cola = actual; // Si se elimina el último nodo
            delete temp;
        }
    }

public:
    ListaEnlazada();  // Constructor
    void insertarPorCabeza(T valor);
    void insertarPorCola(T valor);
    void mostrarLista() const;
    int buscarElemento(std::function<bool(const T&)> condicion) const; 
    void eliminarElemento(std::function<bool(const T&)> condicion); // Basado en una condición
    ~ListaEnlazada();  // Destructor
};

// Implementación de los métodos

template <typename T>
ListaEnlazada<T>::ListaEnlazada() : cabeza(nullptr), cola(nullptr) {}

template <typename T>
void ListaEnlazada<T>::insertarPorCabeza(T valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    if (cabeza == nullptr) {
        cabeza = cola = nuevoNodo;
    } else {
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }
}

template <typename T>
void ListaEnlazada<T>::insertarPorCola(T valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    if (cola == nullptr) {
        cabeza = cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        cola = nuevoNodo;
    }
}

template <typename T>
void ListaEnlazada<T>::mostrarLista() const {
    mostrarListaRecursivo(cabeza);
}

template <typename T>
void ListaEnlazada<T>::eliminarElemento(std::function<bool(const T&)> condicion) {
    int indice = buscarElementoRecursivo(cabeza, condicion, 0);
    if (indice != -1) {
        eliminarNodoEnIndice(indice);
    }
}
template <typename T>
int ListaEnlazada<T>::buscarElemento(std::function<bool(const T&)> condicion) const {
    return buscarElementoRecursivo(cabeza, condicion, 0);
}

template <typename T>
ListaEnlazada<T>::~ListaEnlazada() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

#endif // LISTA_ENLAZADA_H
