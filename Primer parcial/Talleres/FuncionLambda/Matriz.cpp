// Matriz.cpp
#include "Matriz.h"
#include <iostream>
#include <random>

// Constructor de la clase
Matriz::Matriz(int filas, int columnas)
    : filas(filas), columnas(columnas),
      A(filas, std::vector<int>(columnas)),
      B(filas, std::vector<int>(columnas)),
      C(filas, std::vector<int>(columnas, 0)) {}

// Llena una matriz con números aleatorios
void Matriz::llenarAleatorio(std::vector<std::vector<int>>& matriz) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = dis(gen);
        }
    }
}

// Inicializa las matrices A y B con números aleatorios
void Matriz::inicializarMatrices() {
    llenarAleatorio(A);
    llenarAleatorio(B);
}

// Suma las matrices usando una lambda con captura por referencia general [&]
void Matriz::sumarMatricesReferencia() {
    auto sumaRef = [&](auto&& self, int i, int j) -> void {
        if (i == filas) return;
        if (j == columnas) {
            self(self, i + 1, 0);
        } else {
            C[i][j] = A[i][j] + B[i][j];
            self(self, i, j + 1);
        }
    };
    sumaRef(sumaRef, 0, 0);
}

// Suma las matrices usando una lambda con captura específica [this]
void Matriz::sumarMatricesEspecifica() {
    auto sumaEspecifica = [this](auto&& self, int i, int j) -> void {
        if (i == filas) return;
        if (j == columnas) {
            self(self, i + 1, 0);
        } else {
            C[i][j] = A[i][j] + B[i][j];
            self(self, i, j + 1);
        }
    };
    sumaEspecifica(sumaEspecifica, 0, 0);
}

// Suma las matrices usando una lambda con captura combinada [this]
void Matriz::sumarMatricesCombinada() {
    // Captura por referencia el objeto `this`, para acceder a todos los miembros de la clase
    auto sumaCombinada = [this](auto&& self, int i, int j) -> void {
        if (i == filas) return;
        if (j == columnas) {
            self(self, i + 1, 0);  // Llamada recursiva a la siguiente fila
        } else {
            C[i][j] = A[i][j] + B[i][j];  // Sumamos las matrices
            self(self, i, j + 1);  // Llamada recursiva a la siguiente columna
        }
    };
    sumaCombinada(sumaCombinada, 0, 0);  // Iniciar la suma desde la posición (0, 0)
}


// Imprime una matriz con un nombre dado
void Matriz::imprimirMatriz(const std::vector<std::vector<int>>& matriz, const std::string& nombre) const {
    std::cout << nombre << ":\n";
    for (const auto& fila : matriz) {
        for (int elem : fila) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Imprime las matrices A, B y el resultado C
void Matriz::imprimirMatrices() const {
    imprimirMatriz(A, "Matriz A");
    std::cout << std::endl;
    imprimirMatriz(B, "Matriz B");
    std::cout << std::endl;
    imprimirMatriz(C, "Resultado (A + B)");
}
