#include "BTree.h"
#include <iostream>
#include <vector>  // Para usar std::vector

int main() {
    int t;
    std::cout << "Ingrese el grado mínimo del Árbol B: ";
    std::cin >> t;

    BTree tree(t);

    // Leer todas las claves
    std::vector<int> keys;
    int key;
    std::cout << "Ingrese claves (0 para terminar): ";
    while (true) {
        std::cin >> key;
        if (key == 0) break;
        keys.push_back(key);  // Almacenamos las claves en el vector
    }

    // Insertar las claves ordenadas en el árbol
    tree.insertSorted(keys);

    // Mostrar el recorrido en orden del árbol
    std::cout << "\nRecorrido del Árbol B:\n";
    tree.traverse();

    // Mostrar la representación gráfica del árbol
    std::cout << "\nRepresentación del Árbol B en consola:\n";
    tree.printTree();

    return 0;
}
