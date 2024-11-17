#include <iostream>
#include <vector>
#include <random>

int main() {
    // Dimensiones de las matrices
    const int filas = 3;
    const int columnas = 3;

    // Generador de números aleatorios
    std::random_device rd;  // Semilla aleatoria
    std::mt19937 gen(rd()); // Generador basado en Mersenne Twister
    std::uniform_int_distribution<> dis(1, 10); // Distribución uniforme entre 1 y 10

    // Definimos las matrices de ejemplo
    std::vector<std::vector<int>> A(filas, std::vector<int>(columnas));
    std::vector<std::vector<int>> B(filas, std::vector<int>(columnas));
    std::vector<std::vector<int>> C(filas, std::vector<int>(columnas, 0)); // Matriz de resultado

    // Llenamos las matrices A y B con números aleatorios
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            A[i][j] = dis(gen);  // Llenar A con números aleatorios
            B[i][j] = dis(gen);  // Llenar B con números aleatorios
        }
    }

    // Definimos una función lambda recursiva para sumar matrices
    auto sumarMatrices = [&](auto&& sumarMatrices, int i, int j) -> void {
        // Caso base: si hemos recorrido todas las filas y columnas, terminamos
        if (i == filas) return;

        // Sumamos las matrices A y B
        if (j == columnas) {
            sumarMatrices(sumarMatrices, i + 1, 0); // Llamada recursiva a la siguiente fila
        } else {
            C[i][j] = A[i][j] + B[i][j];
            sumarMatrices(sumarMatrices, i, j + 1); // Llamada recursiva a la siguiente columna
        }
    };

    // Llamamos a la lambda recursiva para iniciar la suma desde la posición (0, 0)
    sumarMatrices(sumarMatrices, 0, 0);

    // Imprimimos las matrices A, B y el resultado C
    std::cout << "Matriz A (aleatoria):" << std::endl;
    for (const auto& fila : A) {
        for (int elem : fila) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nMatriz B (aleatoria):" << std::endl;
    for (const auto& fila : B) {
        for (int elem : fila) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nResultado de la suma de matrices (A + B):" << std::endl;
    for (const auto& fila : C) {
        for (int elem : fila) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
