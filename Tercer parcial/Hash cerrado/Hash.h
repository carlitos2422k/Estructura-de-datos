#ifndef HASH_H
#define HASH_H

#include <string>
#include <vector>

class Hash {
private:
    static const int TABLE_SIZE = 29;
    std::vector<std::string> table;
    bool isInteger; // true para hash de enteros, false para strings
    bool useQuadraticProbing; // true para Quadratic Probing, false para Linear Probing
    bool doubleHashing; // true para Double Hashing

    int hashInteger(int value);
    int hashString(const std::string& str);
    int probe(int index, int attempt, int hash1);
    int hash2(int value);
    int doubleHashString(const std::string& str);

public:
    Hash();
    void setHashType(bool useInteger);
    void setProbingMethod(bool useQuadratic);
    void setDoubleHashing(bool useDoubleHashing); // Activa Double Hashing
    bool insert(const std::string& value);
    int findPosition(const std::string& value);
    void display();
};

#endif
