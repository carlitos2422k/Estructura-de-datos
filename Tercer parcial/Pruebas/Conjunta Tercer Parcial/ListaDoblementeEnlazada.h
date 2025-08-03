#ifndef LISTA_DOBLEMENTE_ENLAZADA_H
#define LISTA_DOBLEMENTE_ENLAZADA_H

#include <stdexcept>
#include "Nodo.h"

template<typename T>
class ListaDoblementeEnlazada {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamano;
    
public:
    ListaDoblementeEnlazada();
    ~ListaDoblementeEnlazada();
    
    // No permitir copia para simplificar
    ListaDoblementeEnlazada(const ListaDoblementeEnlazada&) = delete;
    ListaDoblementeEnlazada& operator=(const ListaDoblementeEnlazada&) = delete;
    
    int obtenerTamano() const;
    bool estaVacia() const;
    
    void agregarAlFinal(const T& valor);
    void agregarAlInicio(const T& valor);
    void eliminarUltimo();
    void eliminarPrimero();
    
    T& obtener(int indice);
    const T& obtener(int indice) const;
    
    void limpiar();
    void insertar(int indice, const T& valor);
    void eliminar(int indice);
    
    template<typename Func>
    void paraCada(Func func) const;
};

// Implementación de la plantilla

template<typename T>
ListaDoblementeEnlazada<T>::ListaDoblementeEnlazada() : cabeza(nullptr), cola(nullptr), tamano(0) {
}

template<typename T>
ListaDoblementeEnlazada<T>::~ListaDoblementeEnlazada() {
    limpiar();
}

template<typename T>
int ListaDoblementeEnlazada<T>::obtenerTamano() const {
    return tamano;
}

template<typename T>
bool ListaDoblementeEnlazada<T>::estaVacia() const {
    return tamano == 0;
}

template<typename T>
void ListaDoblementeEnlazada<T>::agregarAlFinal(const T& valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    
    if (estaVacia()) {
        cabeza = cola = nuevoNodo;
    } else {
        nuevoNodo->establecerAnterior(cola);
        cola->establecerSiguiente(nuevoNodo);
        cola = nuevoNodo;
    }
    
    tamano++;
}

template<typename T>
void ListaDoblementeEnlazada<T>::agregarAlInicio(const T& valor) {
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    
    if (estaVacia()) {
        cabeza = cola = nuevoNodo;
    } else {
        nuevoNodo->establecerSiguiente(cabeza);
        cabeza->establecerAnterior(nuevoNodo);
        cabeza = nuevoNodo;
    }
    
    tamano++;
}

template<typename T>
void ListaDoblementeEnlazada<T>::eliminarUltimo() {
    if (estaVacia()) {
        return;
    }
    
    if (cabeza == cola) {
        delete cabeza;
        cabeza = cola = nullptr;
    } else {
        Nodo<T>* temp = cola;
        cola = cola->obtenerAnterior();
        cola->establecerSiguiente(nullptr);
        delete temp;
    }
    
    tamano--;
}

template<typename T>
void ListaDoblementeEnlazada<T>::eliminarPrimero() {
    if (estaVacia()) {
        return;
    }
    
    if (cabeza == cola) {
        delete cabeza;
        cabeza = cola = nullptr;
    } else {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->obtenerSiguiente();
        cabeza->establecerAnterior(nullptr);
        delete temp;
    }
    
    tamano--;
}

template<typename T>
T& ListaDoblementeEnlazada<T>::obtener(int indice) {
    if (indice < 0 || indice >= tamano) {
        throw std::out_of_range("Indice fuera de rango");
    }
    
    Nodo<T>* actual;
    
    // Optimización: acceder desde el extremo más cercano
    if (indice < tamano / 2) {
        actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->obtenerSiguiente();
        }
    } else {
        actual = cola;
        for (int i = tamano - 1; i > indice; i--) {
            actual = actual->obtenerAnterior();
        }
    }
    
    return actual->obtenerDatos();
}

template<typename T>
const T& ListaDoblementeEnlazada<T>::obtener(int indice) const {
    if (indice < 0 || indice >= tamano) {
        throw std::out_of_range("Indice fuera de rango");
    }
    
    Nodo<T>* actual;
    
    // Optimización: acceder desde el extremo más cercano
    if (indice < tamano / 2) {
        actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->obtenerSiguiente();
        }
    } else {
        actual = cola;
        for (int i = tamano - 1; i > indice; i--) {
            actual = actual->obtenerAnterior();
        }
    }
    
    return actual->obtenerDatos();
}

template<typename T>
void ListaDoblementeEnlazada<T>::limpiar() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* temp = actual;
        actual = actual->obtenerSiguiente();
        delete temp;
    }
    
    cabeza = cola = nullptr;
    tamano = 0;
}

template<typename T>
void ListaDoblementeEnlazada<T>::insertar(int indice, const T& valor) {
    if (indice < 0 || indice > tamano) {
        throw std::out_of_range("Indice fuera de rango para insercion");
    }
    
    if (indice == 0) {
        agregarAlInicio(valor);
        return;
    }
    
    if (indice == tamano) {
        agregarAlFinal(valor);
        return;
    }
    
    // Encontrar el nodo en la posición indice
    Nodo<T>* actual;
    if (indice < tamano / 2) {
        actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->obtenerSiguiente();
        }
    } else {
        actual = cola;
        for (int i = tamano - 1; i > indice; i--) {
            actual = actual->obtenerAnterior();
        }
    }
    
    // Insertar antes de actual
    Nodo<T>* nuevoNodo = new Nodo<T>(valor);
    nuevoNodo->establecerAnterior(actual->obtenerAnterior());
    nuevoNodo->establecerSiguiente(actual);
    actual->obtenerAnterior()->establecerSiguiente(nuevoNodo);
    actual->establecerAnterior(nuevoNodo);
    
    tamano++;
}

template<typename T>
void ListaDoblementeEnlazada<T>::eliminar(int indice) {
    if (indice < 0 || indice >= tamano) {
        throw std::out_of_range("Indice fuera de rango para eliminacion");
    }
    
    if (indice == 0) {
        eliminarPrimero();
        return;
    }
    
    if (indice == tamano - 1) {
        eliminarUltimo();
        return;
    }
    
    // Encontrar el nodo en la posición indice
    Nodo<T>* actual;
    if (indice < tamano / 2) {
        actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->obtenerSiguiente();
        }
    } else {
        actual = cola;
        for (int i = tamano - 1; i > indice; i--) {
            actual = actual->obtenerAnterior();
        }
    }
    
    // Eliminar el nodo
    actual->obtenerAnterior()->establecerSiguiente(actual->obtenerSiguiente());
    actual->obtenerSiguiente()->establecerAnterior(actual->obtenerAnterior());
    delete actual;
    
    tamano--;
}

template<typename T>
template<typename Func>
void ListaDoblementeEnlazada<T>::paraCada(Func func) const {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        func(actual->obtenerDatos());
        actual = actual->obtenerSiguiente();
    }
}

#endif // LISTA_DOBLEMENTE_ENLAZADA_H