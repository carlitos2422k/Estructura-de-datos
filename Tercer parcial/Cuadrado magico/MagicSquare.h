#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

#include <vector>

class MagicSquare {
private:
    int size; // Tamaño del cuadrado mágico (n x n)
    std::vector<std::vector<int>> square; // Matriz para el cuadrado mágico

    void fillOdd();    // Método privado para llenar el cuadrado mágico impar
    void fillEven();   // Método privado para llenar el cuadrado mágico par

public:
    MagicSquare(int n); // Constructor
    void display();     // Método público para imprimir el cuadrado mágico
};

#endif // MAGIC_SQUARE_H
