#pragma once
#include <iostream>
#include <string>

using namespace std;

template<typename T>
class NodoDoble {
private:
    T nombre;
    T apellido;
    T cedula;
    T correo;
    NodoDoble* siguiente;
    NodoDoble* anterior;
public:
    NodoDoble(T, T, T, T);
    void setNombre(T);
    T getNombre();
    void setApellido(T);
    T getApellido();
    void setCedula(T);
    T getCedula();
    void setCorreo(T);
    T getCorreo();
    void setSiguiente(NodoDoble*);
    NodoDoble* getSiguiente();
    void setAnterior(NodoDoble*);
    NodoDoble* getAnterior();
    template <typename U> friend class ListaDoble;
};
