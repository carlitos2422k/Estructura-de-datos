#include "NodoDoble.h"

template<typename T>
NodoDoble<T>::NodoDoble(T _nombre, T _apellido, T _cedula, T _correo) {
    nombre = _nombre;
    apellido = _apellido;
    cedula = _cedula;
    correo = _correo;
    siguiente = nullptr;
    anterior = nullptr;
}

template<typename T>
void NodoDoble<T>::setNombre(T _nombre) {
    nombre = _nombre;
}

template<typename T>
T NodoDoble<T>::getNombre() {
    return nombre;
}

template<typename T>
void NodoDoble<T>::setApellido(T _apellido) {
    apellido = _apellido;
}

template<typename T>
T NodoDoble<T>::getApellido() {
    return apellido;
}

template<typename T>
void NodoDoble<T>::setCedula(T _cedula) {
    cedula = _cedula;
}

template<typename T>
T NodoDoble<T>::getCedula() {
    return cedula;
}

template<typename T>
void NodoDoble<T>::setCorreo(T _correo) {
    correo = _correo;
}

template<typename T>
T NodoDoble<T>::getCorreo() {
    return correo;
}

template<typename T>
void NodoDoble<T>::setSiguiente(NodoDoble* _siguiente) {
    siguiente = _siguiente;
}

template<typename T>
NodoDoble<T>* NodoDoble<T>::getSiguiente() {
    return siguiente;
}

template<typename T>
void NodoDoble<T>::setAnterior(NodoDoble* _anterior) {
    anterior = _anterior;
}

template<typename T>
NodoDoble<T>* NodoDoble<T>::getAnterior() {
    return anterior;
}
