#pragma once
#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Nodo {
private:
    T nombre;
    T apellido;
    T cedula;
    T correo;
    Nodo* siguiente;
public:
    Nodo(T, T, T, T);
    void setNombre(T);
    T getNombre();
    void setApellido(T);
    T getApellido();
    void setCedula(T);
    T getCedula();
    void setCorreo(T);
    T getCorreo();
    void setSiguiente(Nodo*);
    Nodo* getSiguiente();
    template <typename U> friend class Lista_Circular;
};
