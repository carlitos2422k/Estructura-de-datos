/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los m�todos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#pragma once
#include "Nodo.h"

template<typename T>
class ListaDoble {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
public:
    ListaDoble();
    void Insertar(T);
    void InsertarCabeza(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
};



