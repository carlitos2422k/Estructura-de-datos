/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista circular cifrado               *
 * Autor:                          Carlos Perez                                        *
 * Fecha de creacion:              04/12/2024                                          *
 * Fecha de modificacion:          04/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#pragma once
#include "Nodo.h"
#include <iostream>
template<typename T>
class Lista_Circular {
private:
    Nodo<T>* cabeza;
public:
    Lista_Circular();
    void InsertarPorCabeza(T, T, T, T);
    void InsertarPorCola(T, T, T, T);
    void Mostrar();
    void BuscarPorCedula(T);
    void EliminarNodo(T);  // Eliminar nodo por completo
    void EliminarDatosNodo(T); // Eliminar datos de un nodo
    void Cifrar(char a);
    void setConsoleColor(int color);
    //void EliminarCampoNodo(T);
};
