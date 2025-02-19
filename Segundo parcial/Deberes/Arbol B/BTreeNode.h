#ifndef BTREENODE_H
#define BTREENODE_H

#include <vector>
#include <iostream>
#include <sstream>
#include <queue>

class BTreeNode {
private:
    int t; // Grado mínimo del árbol
    std::vector<int> keys; // Claves del nodo
    std::vector<BTreeNode*> children; // Punteros a los hijos
    bool isLeaf; // Indica si es hoja

public:
    BTreeNode(int t, bool isLeaf);
    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);
    void traverse(std::ostream& out);
    void printNode(std::ostream& out, int level, int indent);

    friend class BTree;
};

#endif
