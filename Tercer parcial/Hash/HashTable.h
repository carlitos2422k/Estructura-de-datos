#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <bitset>

class HashTable {
private:
    std::vector<std::list<std::string>> table;
    int tableSize;

    int hashFunction(const std::string& key);
    int hashFunction(int key);

public:
    HashTable(int size);
    void insert(const std::string& value);
    void insert(int value);
    void display();
};

#endif // HASHTABLE_H