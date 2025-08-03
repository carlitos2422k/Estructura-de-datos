#include "V.h"
#include <iostream>

// Constructor que recibe un arreglo de valores
V::V(double x[], int size) {
    cabeza = nullptr;
    for (int i = 0; i < size; i++) {
        if (x[i] != 0) {
            Nodo* nuevoNodo = new Nodo(i, x[i], cabeza);
            cabeza = nuevoNodo;
        }
    }
}

// Destructor para liberar la memoria
V::~V() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
}

// Método auxiliar para buscar un nodo por índice
Nodo* V::buscarNodo(int indice) const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->indice == indice) {
            return actual;
        }
        actual = actual->sig;
    }
    return nullptr;
}

// Método para calcular el producto punto entre dos vectores
double V::pPunto(const V& otro) {
    double resultado = 0;
    Nodo* actual = cabeza;

    // Iteramos sobre los elementos de la lista del vector actual
    while (actual != nullptr) {
        Nodo* nodoOtro = otro.buscarNodo(actual->indice);
        if (nodoOtro != nullptr) {
            resultado += actual->valor * nodoOtro->valor;
        }
        actual = actual->sig;
    }
    return resultado;
}

// Método para proyectar el vector, eliminando un elemento en la posición indicada
V V::proyectar(int indiceEliminar) {
    Nodo* actual = cabeza;
    Nodo* previo = nullptr;

    while (actual != nullptr) {
        if (actual->indice == indiceEliminar) {
            if (previo == nullptr) {
                cabeza = actual->sig;  // Eliminar el primer nodo
            } else {
                previo->sig = actual->sig;  // Eliminar nodo intermedio
            }
            delete actual;
            return *this;  // Devolver el vector con el elemento eliminado
        }
        previo = actual;
        actual = actual->sig;
    }

    // Si el índice no se encuentra, devolvemos el vector original
    return *this;
}
