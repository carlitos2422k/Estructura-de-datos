#include "Nodo.h"

// Método para verificar si el árbol es un ABM
bool Nodo::esABM(Nodo* x) {
    // Caso árbol vacío
    if (x == nullptr)
        return true;
    
    // Caso árbol sin subárboles
    if (x->izq == nullptr && x->der == nullptr)
        return true;
    
    // Caso árbol izquierdo vacío
    if (x->izq == nullptr)
        return x->valor <= x->der->valor && esABM(x->der);
    
    // Caso árbol derecho vacío
    if (x->der == nullptr)
        return x->valor <= x->izq->valor && esABM(x->izq);
    
    // Caso general
    return x->valor <= x->izq->valor && x->valor <= x->der->valor &&
           esABM(x->izq) && esABM(x->der);
}

// Método para juntar dos árboles
Nodo* Nodo::juntar(Nodo* x, Nodo* y) {
    // Caso ambos árboles vacíos
    if (x == nullptr && y == nullptr)
        return nullptr;
    
    // Caso árbol izquierdo vacío
    if (x == nullptr)
        return new Nodo(y->valor, juntar(y->izq, nullptr), juntar(y->der, nullptr));
    
    // Caso árbol derecho vacío
    if (y == nullptr)
        return new Nodo(x->valor, juntar(x->izq, nullptr), juntar(x->der, nullptr));
    
    // Caso general
    if (x->valor <= y->valor)
        return new Nodo(x->valor, juntar(x->izq, x->der), juntar(y, nullptr));
    else
        return new Nodo(y->valor, juntar(x, nullptr), juntar(y->izq, y->der));
}
