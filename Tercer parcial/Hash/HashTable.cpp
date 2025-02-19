#include "HashTable.h"

using namespace std;

HashTable::HashTable(int size) : tableSize(size) {
    table.resize(tableSize);
}

int HashTable::hashFunction(const string& key) {
    unsigned int result = 0;
    for (char c : key) {
        unsigned int binaryValue = static_cast<unsigned int>(c);
        result ^= binaryValue; // XOR operation with binary value
        result = (result << 1) | (result >> 31);  // Rotate left by 1 bit
    }
    return result % tableSize;
}

int HashTable::hashFunction(int key) {
    unsigned int result = 0;
    for (int i = 0; i < 32; ++i) {
        int bit = (key >> i) & 1;
        result ^= bit;
        result = (result << 1) | (result >> 31);
    }
    return result % tableSize;
}

void HashTable::insert(const string& value) {
    int index = hashFunction(value);
    table[index].push_back(value);
    cout << "Inserted '" << value << "' at index " << index << endl;
}

void HashTable::insert(int value) {
    int index = hashFunction(value);
    table[index].push_back(to_string(value));
    cout << "Inserted '" << value << "' at index " << index << endl;
}

void HashTable::display() {
    for (int i = 0; i < tableSize; ++i) {
        cout << "Index " << i << ": ";
        for (const auto& element : table[i]) {
            cout << element << " -> ";
        }
        cout << "NULL" << endl;
    }
}