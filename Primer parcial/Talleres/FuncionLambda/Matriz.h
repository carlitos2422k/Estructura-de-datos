// Matriz.h
#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <string>

class Matriz {
private:
    int filas;
    int columnas;
    std::vector<std::vector<int>> A;
    std::vector<std::vector<int>> B;
    std::vector<std::vector<int>> C;

    void llenarAleatorio(std::vector<std::vector<int>>& matriz);
    void imprimirMatriz(const std::vector<std::vector<int>>& matriz, const std::string& nombre) const;

public:
    Matriz(int filas, int columnas);
    void inicializarMatrices();
    
    // Métodos para sumar matrices con diferentes capturas de lambdas
    void sumarMatricesReferencia();
    void sumarMatricesEspecifica();
    void sumarMatricesCombinada();
    
    void imprimirMatrices() const;
};

#endif // MATRIZ_H
