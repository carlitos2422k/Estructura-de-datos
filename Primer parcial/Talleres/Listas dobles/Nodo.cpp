/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los m�todos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#include "Nodo.h"

// Constructor
template<typename T>
Nodo<T>::Nodo(T _dato) {
    dato = _dato;
    siguiente = nullptr;
    anterior = nullptr;
}

// Setters
template<typename T>
void Nodo<T>::setDato(T _dato) {
    dato = _dato;
}

template<typename T>
void Nodo<T>::setSiguiente(Nodo* _siguiente) {
    siguiente = _siguiente;
}

template<typename T>
void Nodo<T>::setAnterior(Nodo* _anterior) {
    anterior = _anterior;
}

// Getters
template<typename T>
T Nodo<T>::getDato() {
    return dato;
}

template<typename T>
Nodo<T>* Nodo<T>::getSiguiente() {
    return siguiente;
}

template<typename T>
Nodo<T>* Nodo<T>::getAnterior() {
    return anterior;
}
