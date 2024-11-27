#pragma once
#include "Nodo.h"

template<typename T>
class Lista_Simple {
private:
    Nodo<T>* cabeza;
    Nodo<T>* BuscarNodoPorCedula(T cedula);
public:
    Lista_Simple();
    void Insertar(T, T, T, T);
    void Mostrar();
    void BuscarPorCedula(T);
    void EliminarNodoPorCedula(T cedula);
    void LimpiarDatosNodo(T cedula);
    //void ElegirDatoAEliminar(T);

    
};
