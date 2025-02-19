#include "BTreeNode.h"

BTreeNode::BTreeNode(int t, bool isLeaf)
    : t(t), isLeaf(isLeaf) {}

void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    // Si el nodo es una hoja, insertamos la clave directamente
    if (isLeaf) {
        keys.push_back(0); // Reservamos espacio para la nueva clave
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i]; // Desplazamos las claves hacia la derecha
            i--;
        }
        keys[i + 1] = key; // Insertamos la nueva clave en la posición correcta
    } else {
        // Si el nodo no es hoja, buscamos el hijo adecuado para insertar la clave
        while (i >= 0 && keys[i] > key) i--;
        i++;

        // Si el hijo está lleno, lo dividimos
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);

            // Después de la división, debemos revisar si la clave debe ir al subárbol izquierdo o derecho
            if (keys[i] < key) i++;
        }

        // Insertamos la clave en el subárbol adecuado
        children[i]->insertNonFull(key);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    // Creamos un nuevo nodo z que tomará las claves mayores a la mediana de y
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    if (!y->isLeaf) z->children.assign(y->children.begin() + t, y->children.end());

    // Reducimos el tamaño del nodo original (y)
    y->keys.resize(t - 1);
    y->children.resize(t);

    // Desplazamos las claves e hijos del nodo padre
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}



void BTreeNode::traverse(std::ostream& out) {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) children[i]->traverse(out);
        out << keys[i] << " ";
    }
    if (!isLeaf) children[i]->traverse(out);
}

void BTreeNode::printNode(std::ostream& out, int level, int childIndex) {
    // Imprimimos las claves del nodo actual
    out << std::string(level * 4, ' ') << "["; // 4 espacios por nivel para la indentación
    for (size_t i = 0; i < keys.size(); i++) {
        out << keys[i];
        if (i != keys.size() - 1) out << " ";
    }
    out << "]\n";

    // Imprimimos los hijos si el nodo no es una hoja
    if (!isLeaf) {
        for (size_t i = 0; i < children.size(); i++) {
            // Imprimimos cada hijo, con un índice que indique si es el hijo izquierdo o derecho
            std::string childType = (i == 0) ? "Hijo izquierdo" : (i == children.size() - 1) ? "Hijo derecho" : "Hijo";
            out << std::string((level + 1) * 4, ' ') << childType << "\n";
            children[i]->printNode(out, level + 1, i);
        }
    }
}

