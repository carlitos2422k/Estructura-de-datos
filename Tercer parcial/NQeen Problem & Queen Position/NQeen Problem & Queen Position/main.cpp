#include "NQueens.h"
#include <iostream>
#include <conio.h> // Para _getch() en Windows

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMenu(int selectedOption) {
    clearScreen();
    std::cout << "=== N-Queens Solver ===\n\n";
    
    if (selectedOption == 0) {
        std::cout << "[*] 1. Resolver N-Queens\n";
        std::cout << "    2. Visualizar movimientos de Reina\n";
        std::cout << "    3. Salir\n";
    } else if (selectedOption == 1) {
        std::cout << "    1. Resolver N-Queens\n";
        std::cout << "[*] 2. Visualizar movimientos de Reina\n";
        std::cout << "    3. Salir\n";
    } else {
        std::cout << "    1. Resolver N-Queens\n";
        std::cout << "    2. Visualizar movimientos de Reina\n";
        std::cout << "[*] 3. Salir\n";
    }
    
    std::cout << "\nUse W/S o flechas arriba/abajo para moverse\n";
    std::cout << "Presione Enter para seleccionar\n";
}

int main() {
    int selectedOption = 0;
    bool inMenu = true;

    while (inMenu) {
        displayMenu(selectedOption);
        int key = _getch();
        
        // Detectar si es una flecha
        if (key == 224 || key == 0) {
            key = _getch();
            switch (key) {
                case 72: // Flecha arriba
                    selectedOption = (selectedOption - 1 + 3) % 3;
                    break;
                case 80: // Flecha abajo
                    selectedOption = (selectedOption + 1) % 3;
                    break;
            }
        }
        // Detectar W/S
        else if (key == 'w' || key == 'W') {
            selectedOption = (selectedOption - 1 + 3) % 3;
        }
        else if (key == 's' || key == 'S') {
            selectedOption = (selectedOption + 1) % 3;
        }
        // Detectar Enter
        else if (key == 13) {
            if (selectedOption == 2) { // Opción Salir
                inMenu = false;
                break;
            }

            clearScreen();
            int n;
            std::cout << "Ingrese el tamanio del tablero (N x N): ";
            std::cin >> n;

            if (selectedOption == 0) {
                if (n < 4) {
                    std::cout << "El tamanio debe ser al menos 4x4 para tener solucion.\n";
                    std::cout << "\nPresione cualquier tecla para continuar...";
                    _getch();
                    continue;
                }

                NQueens queens(n);
                std::cout << "Resolviendo el problema de " << n << " reinas...\n";
                std::cout << "La ventana grafica se abrira automaticamente.\n";
                std::cout << "El proceso se registrara en 'queens_steps.txt'\n\n";
                
                if (queens.solveNQueens(0)) {
                    std::cout << "¡Solucion encontrada!\n";
                    std::cout << "Numero total de pasos: " << queens.getSteps() << "\n";
                    std::cout << "Maximo numero de pasos en una rama: " << queens.getMaxSteps() << "\n";
                    queens.run();
                } else {
                    std::cout << "No se encontro solucion para " << n << " reinas.\n";
                }
            } else if (selectedOption == 1) {
                NQueens queens(n);
                int row, col;
                std::cout << "Ingrese la posicion de la reina (fila columna): ";
                std::cin >> row >> col;
                row--; col--; // Convertir a índices base 0
                
                if (row >= 0 && row < n && col >= 0 && col < n) {
                    queens.showQueenMoves(row, col);
                } else {
                    std::cout << "Posicion invalida\n";
                    std::cout << "\nPresione cualquier tecla para continuar...";
                    _getch();
                }
            }
            
            std::cout << "\nPresione cualquier tecla para volver al menu...";
            _getch();
        }
    }
    
    clearScreen();
    std::cout << "Gracias por usar N-Queens Solver!\n";
    return 0;
}