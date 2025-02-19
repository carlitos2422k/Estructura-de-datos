#ifndef HASH_H
#define HASH_H

#include <string>
#include <vector>

class Hash {
private:
    static const int TABLE_SIZE = 29;
    std::vector<std::string> table;
    bool isInteger; // true para hash de enteros, false para strings

    int hashInteger(int value);
    int hashString(const std::string& str);
    
public:
    Hash();
    void setHashType(bool useInteger);
    bool insert(const std::string& value);
    int findPosition(const std::string& value);
    void display();
};

#endif
