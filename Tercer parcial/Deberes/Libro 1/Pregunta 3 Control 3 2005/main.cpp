#include <iostream>
#include "Logico.h"
#include "Nodo.h"

int main() {
    // Crear los valores lógicos
    Logico a(0);
    Logico b(1);
    Logico c(0);

    // Crear operadores
    std::string orOp = "^";
    std::string notOp = "~";

    // Construir el árbol lógico para la expresión: (a ∧ b) ∨ (¬c)
    Nodo* nodoA = new Nodo(&a);
    Nodo* nodoB = new Nodo(&b);
    Nodo* nodoC = new Nodo(&c);

    Nodo* notC = new Nodo(&notOp);  // Nodo para negación
    notC->izq = nodoC;

    Nodo* andAB = new Nodo(&orOp);  // Nodo para conjunción
    andAB->izq = nodoA;
    andAB->der = nodoB;

    Nodo* orRoot = new Nodo(&orOp);  // Nodo para disyunción
    orRoot->izq = andAB;
    orRoot->der = notC;

    // Evaluar la expresión
    Logico resultado = Logico::evaluar(orRoot);
    std::cout << "Resultado de la expresión: " << resultado.evaluar(nullptr).getValue() << std::endl;

    return 0;
}
