#include "Logico.h"
#include <iostream>

Logico::Logico(int x) : v(x) {}

Logico Logico::negacion() {
    return Logico(v == 0 ? 1 : 0);
}

Logico Logico::conjuncion(Logico x) {
    return Logico(v == 1 && x.v == 1 ? 1 : 0);
}

Logico Logico::disyuncion(Logico x) {
    return Logico(v == 1 || x.v == 1 ? 1 : 0);
}

Logico Logico::evaluar(Nodo* raiz) {
    // Caso árbol vacío
    if (raiz == nullptr) {
        return Logico(0);
    }

    // Caso operando
    if (raiz->izq == nullptr && raiz->der == nullptr) {
        return *((Logico*)raiz->valor);  // Evaluamos el valor lógico almacenado en el nodo
    }

    // Evaluar los subárboles izquierdo y derecho
    Logico a = evaluar(raiz->izq);
    Logico b = evaluar(raiz->der);

    // Evaluar operaciones
    std::string operador = *((std::string*)raiz->valor);
    if (operador == "~") {
        return b.negacion();
    }
    if (operador == "^") {
        return a.conjuncion(b);
    }
    return a.disyuncion(b);
}
