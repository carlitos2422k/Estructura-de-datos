/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Lista simple                                        *
 * Autor:                          Carlos Pérez                                        *
 * Fecha de creacion:              18/11/2024                                          *
 * Fecha de modificacion:          20/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#pragma once
//#include "Nodo.cpp"
#include "Nodo.h"
using namespace std;

template<typename T>
class Lista_Simple {
private:
    Nodo<T>* cabeza;
public:
    Lista_Simple();
    void Insertar_cabeza(T);
    //void Insertar_cola(T);
    void Buscar(T);
    void Eliminar(T);
    void EliminarDato(T);
    void Mostrar();
    bool contains(T _dato);
};

