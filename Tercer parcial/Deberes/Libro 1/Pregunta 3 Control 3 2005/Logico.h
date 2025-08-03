#ifndef LOGICO_H
#define LOGICO_H

class Logico {
private:
    int v;  // Representa el valor lógico (0 o 1)

public:
    Logico(int x);  // Constructor que asigna el valor lógico
    Logico negacion();  // Operación lógica NOT
    Logico conjuncion(Logico x);  // Operación lógica AND
    Logico disyuncion(Logico x);  // Operación lógica OR
    static Logico evaluar(Nodo* raiz);  // Método que evalúa el árbol lógico

    int getValue() const { return v; }  // Método para obtener el valor lógico
};

#endif
