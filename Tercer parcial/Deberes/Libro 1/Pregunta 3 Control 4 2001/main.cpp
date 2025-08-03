#include <iostream>
#include "Nodo.h"

int main() {
    // Crear nodos de ejemplo
    Nodo* n1 = new Nodo(2);
    Nodo* n2 = new Nodo(5);
    Nodo* n3 = new Nodo(4);
    Nodo* n4 = new Nodo(8);
    Nodo* n5 = new Nodo(5);
    Nodo* n6 = new Nodo(7);

    // Estructurar los árboles como ejemplo
    n1->izq = n2;
    n1->der = n3;
    n2->izq = n4;
    n2->der = n5;
    n3->izq = n6;

    // Verificar si es un ABM
    if (n1->esABM(n1)) {
        std::cout << "El árbol es un ABM." << std::endl;
    } else {
        std::cout << "El árbol no es un ABM." << std::endl;
    }

    // Crear otro árbol para probar la función juntar
    Nodo* n7 = new Nodo(3);
    Nodo* n8 = new Nodo(6);
    n7->izq = n8;

    Nodo* nuevoArbol = Nodo::juntar(n1, n7);

    // Verificar si el árbol combinado es un ABM
    if (nuevoArbol->esABM(nuevoArbol)) {
        std::cout << "El árbol combinado es un ABM." << std::endl;
    } else {
        std::cout << "El árbol combinado no es un ABM." << std::endl;
    }

    // Limpiar memoria
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
    delete n7;
    delete n8;
    delete nuevoArbol;

    return 0;
}
