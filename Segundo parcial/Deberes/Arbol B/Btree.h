#ifndef BTREE_H
#define BTREE_H

#include "BTreeNode.h"
#include <fstream>
#include <string>

class BTree {
private:
    BTreeNode* root;
    int t;

public:
    BTree(int t);
    void insert(int key);
    void traverse();
    void printTree();
    void insertSorted(std::vector<int> keys);
};

#endif
