#include "BTree.h"
#include <algorithm> 
BTree::BTree(int t) : t(t), root(nullptr) {}

void BTree::insert(int key) {
    if (!root) {
        // Si el árbol está vacío, creamos la raíz
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            // Si la raíz está llena, creamos un nuevo nodo raíz
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root); // La raíz actual es hijo de la nueva raíz
            s->splitChild(0, root); // Dividimos la raíz
            root = s; // La nueva raíz es ahora la raíz del árbol
        }
        // Insertamos la clave en la raíz
        root->insertNonFull(key);
    }
}

void BTree::insertSorted(std::vector<int> keys) {
    // Ordenamos las claves antes de insertarlas
    std::sort(keys.begin(), keys.end());

    // Insertamos las claves ordenadas una por una
    for (int key : keys) {
        insert(key);
    }
}

void BTree::traverse() {
    if (root) root->traverse(std::cout);
}

void BTree::printTree() {
    if (root) root->printNode(std::cout, 0, 0);
    else std::cout << "El Árbol B está vacío.\n";
}

