#ifndef V_H
#define V_H
#include "Nodo.h"

class V {
private:
    Nodo* cabeza;  // Cabeza de la lista enlazada que representa el vector

public:
    // Constructor que recibe un arreglo de valores
    V(double x[], int size);
    
    // Método para calcular el producto punto entre dos vectores
    double pPunto(const V& otro);
    
    // Método para proyectar el vector, eliminando un elemento en la posición indicada
    V proyectar(int indiceEliminar);
    
    // Destructor para liberar la memoria
    ~V();

private:
    // Método auxiliar para buscar un nodo por índice
    Nodo* buscarNodo(int indice) const;  // Cambié a "const" porque no modifica el objeto
};

#endif
