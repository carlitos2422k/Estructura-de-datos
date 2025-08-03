#include <iostream>
#include "Nodo.h"

int main() {
    // Crear nodos de ejemplo
    Nodo* n1 = new Nodo("A");
    Nodo* n2 = new Nodo("B");
    Nodo* n3 = new Nodo("C");
    Nodo* n4 = new Nodo("D");
    Nodo* n5 = new Nodo("E");
    Nodo* n6 = new Nodo("F");

    // Estructurar los árboles como ejemplo para el primer árbol
    n1->izq = n2;
    n1->der = n3;
    n2->izq = n4;
    n2->der = n5;
    n3->izq = n6;

    // Crear el segundo árbol
    Nodo* n7 = new Nodo("A");
    Nodo* n8 = new Nodo("C");
    Nodo* n9 = new Nodo("B");
    Nodo* n10 = new Nodo("F");
    Nodo* n11 = new Nodo("E");
    Nodo* n12 = new Nodo("D");

    // Estructurar el segundo árbol
    n7->izq = n8;
    n7->der = n9;
    n8->der = n10;
    n9->izq = n11;
    n9->der = n12;

    // Verificar si los dos árboles son espejos
    if (Nodo::espejos(n1, n7)) {
        std::cout << "Los árboles son espejos." << std::endl;
    } else {
        std::cout << "Los árboles no son espejos." << std::endl;
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
    delete n9;
    delete n10;
    delete n11;
    delete n12;

    return 0;
}
