/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista circular cifrado               *
 * Autor:                          Carlos Perez                                        *
 * Fecha de creacion:              04/12/2024                                          *
 * Fecha de modificacion:          04/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#include "Nodo.h"

template<typename T>
Nodo<T>::Nodo(T _nombre, T _apellido, T _cedula, T _correo) {
    nombre = _nombre;
    apellido = _apellido;
    cedula = _cedula;
    correo = _correo;
    siguiente = nullptr;
}

template<typename T>
void Nodo<T>::setNombre(T _nombre) {
    nombre = _nombre;
}

template<typename T>
T Nodo<T>::getNombre() {
    return nombre;
}

template<typename T>
void Nodo<T>::setApellido(T _apellido) {
    apellido = _apellido;
}

template<typename T>
T Nodo<T>::getApellido() {
    return apellido;
}

template<typename T>
void Nodo<T>::setCedula(T _cedula) {
    cedula = _cedula;
}

template<typename T>
T Nodo<T>::getCedula() {
    return cedula;
}

template<typename T>
void Nodo<T>::setCorreo(T _correo) {
    correo = _correo;
}

template<typename T>
T Nodo<T>::getCorreo() {
    return correo;
}

template<typename T>
void Nodo<T>::setSiguiente(Nodo* _siguiente) {
    siguiente = _siguiente;
}

template<typename T>
Nodo<T>* Nodo<T>::getSiguiente() {
    return siguiente;
}
