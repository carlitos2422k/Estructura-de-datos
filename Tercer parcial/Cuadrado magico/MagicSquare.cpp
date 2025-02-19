#include "MagicSquare.h"
#include <iostream>
#include <iomanip> // Para formatear la salida
#include <stdexcept>

MagicSquare::MagicSquare(int n) {
    if (n < 3) {
        throw std::invalid_argument("El tamaño debe ser al menos 3.");
    }

    size = n;
    square = std::vector<std::vector<int>>(size, std::vector<int>(size, 0)); // Inicializa la matriz con ceros

    if (size % 2 == 1) {
        fillOdd();  // Llama al método para llenar cuadrado impar
    } else {
        fillEven(); // Llama al método para llenar cuadrado par
    }
}

void MagicSquare::fillOdd() {
    int i = 0;               // Empieza en la primera fila
    int j = size / 2;        // Empieza en la columna central
    int num = 1;             // Primer número a colocar

    while (num <= size * size) {
        square[i][j] = num;  // Coloca el número en la posición actual

        // Calcula la siguiente posición según la fórmula
        int nextI = (i - 1 + size) % size; // Mueve "hacia arriba" cíclicamente
        int nextJ = (j + 1) % size;        // Mueve "a la derecha" cíclicamente

        if (square[nextI][nextJ] != 0) {
            // Si la celda calculada ya está ocupada, baja una fila
            nextI = (i + 1) % size;
            nextJ = j;
        }

        // Avanza a la siguiente posición
        i = nextI;
        j = nextJ;
        num++;
    }
}

void MagicSquare::fillEven() {
    int n = size;
    int total = n * n;

    // Llena la matriz con números en orden ascendente
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            square[i][j] = i * n + j + 1;
        }
    }

    // Intercambia posiciones para cumplir las reglas del cuadrado mágico
    for (int i = 0; i < n / 4; ++i) {
        for (int j = 0; j < n / 4; ++j) {
            square[i][j] = total - square[i][j] + 1; // Esquina superior izquierda
            square[i][n - j - 1] = total - square[i][n - j - 1] + 1; // Esquina superior derecha
            square[n - i - 1][j] = total - square[n - i - 1][j] + 1; // Esquina inferior izquierda
            square[n - i - 1][n - j - 1] = total - square[n - i - 1][n - j - 1] + 1; // Esquina inferior derecha
        }
    }

    // Cambia los números en las columnas centrales
    for (int i = n / 4; i < n - n / 4; ++i) {
        for (int j = n / 4; j < n - n / 4; ++j) {
            square[i][j] = total - square[i][j] + 1; // Centro de la matriz
        }
    }
}

void MagicSquare::display() {
    for (const auto& row : square) {
        for (int val : row) {
            std::cout << std::setw(4) << val; // Imprime cada número con formato
        }
        std::cout << std::endl;
    }
}
