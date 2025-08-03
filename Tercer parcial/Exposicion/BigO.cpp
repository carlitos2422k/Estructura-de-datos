#include "BigO.h"

BigO::BigO(std::string notation) : notation(notation) {}

std::string BigO::getNotation() const {
    return notation;
}

BigO BigO::operator+(const BigO& other) const {
    return (notation > other.notation) ? *this : other;
}

BigO BigO::operator*(const BigO& other) const {
    return BigO("O(" + notation + " * " + other.notation + ")");
}

void BigO::fundamentals() {
    std::cout << "\n--- Fundamentos de la Notación O ---" << std::endl;
    std::cout << "Definición: La notación O describe el crecimiento asintótico de una función." << std::endl;
    std::cout << "Ejemplo: Si f(n) = 3n^2 + 5n + 10, su notación O es O(n^2) porque domina n^2." << std::endl;
}

void BigO::manipulationRules() {
    std::cout << "\n--- Reglas de Manipulación ---" << std::endl;
    std::cout << "Regla de la suma: O(n) + O(n^2) = O(n^2)" << std::endl;
    std::cout << "Regla del producto: O(n) * O(n log n) = O(n^2 log n)" << std::endl;
    std::cout << "Regla de omisión de constantes: O(3n) = O(n)" << std::endl;
}

void BigO::applications() {
    std::cout << "\n--- Aplicaciones y Comparación de Algoritmos ---" << std::endl;
    std::cout << "Ejemplo: Comparación de algoritmos de ordenamiento." << std::endl;
    std::cout << "BubbleSort: O(n^2) vs MergeSort: O(n log n), el segundo es más eficiente." << std::endl;
}