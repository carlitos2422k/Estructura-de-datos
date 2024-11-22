#include "Matriz.h"
#include <iostream>

int main() {
    Matriz matriz(3, 3);  // Creamos un objeto Matriz con 3 filas y 3 columnas
    matriz.inicializarMatrices();  // Llenamos las matrices A y B con números aleatorios

    std::cout << "Usando lambda con captura por referencia general [&]:\n";
    matriz.sumarMatricesReferencia();  // Suma las matrices con captura por referencia
    matriz.imprimirMatrices();  // Imprime las matrices A, B y el resultado C

    std::cout << "\nUsando lambda con captura específica [this]:\n";
    matriz.sumarMatricesEspecifica();  // Suma las matrices con captura específica
    matriz.imprimirMatrices();  // Imprime las matrices A, B y el resultado C

    std::cout << "\nUsando lambda con captura combinada [=, &C]:\n";
    matriz.sumarMatricesCombinada();  // Suma las matrices con captura combinada
    matriz.imprimirMatrices();  // Imprime las matrices A, B y el resultado C

    return 0;
}
