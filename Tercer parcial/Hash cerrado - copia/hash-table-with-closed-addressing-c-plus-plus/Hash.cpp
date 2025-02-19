#include "Hash.h"
#include <iostream>
#include <bitset>

Hash::Hash() : table(TABLE_SIZE), isInteger(true) {}

void Hash::setHashType(bool useInteger) {
    isInteger = useInteger;
    table = std::vector<std::string>(TABLE_SIZE); // Limpia la tabla
}

int Hash::hashInteger(int value) {
    return value % TABLE_SIZE;
}

int Hash::hashString(const std::string& str) {
    unsigned long hash = 0;

    // Recorrer la cadena de derecha a izquierda
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        char c = *it;

        // 1. Sumar el valor del carácter al hash
        hash += static_cast<unsigned long>(c);

        // 2. Aplicar XOR y desplazamientos solo si no es el último carácter
        if (it + 1 != str.rend()) {
            unsigned long xorPart = (hash >> 28) & 0xF; // 4 bits más significativos

            hash = (hash << 4) | xorPart;  // Agregar XOR al final del hash
            hash += xorPart << 10;         // Sumar el XOR desplazado 10 posiciones
        }
    }

    // 3. Aplicar módulo para obtener la posición en la tabla
    return hash % TABLE_SIZE;
}


bool Hash::insert(const std::string& value) {
    int index;
    if(isInteger) {
        try {
            index = hashInteger(std::stoi(value));
        } catch(...) {
            std::cout << "Error: Valor no válido para hash de enteros\n";
            return false;
        }
    } else {
        index = hashString(value);
    }
    
    int originalIndex = index;
    
    // Sondeo lineal
    while(!table[index].empty()) {
        index = (index + 1) % TABLE_SIZE;
        if(index == originalIndex) {
            std::cout << "Tabla llena\n";
            return false;
        }
    }
    
    table[index] = value;
    return true;
}

int Hash::findPosition(const std::string& value) {
    int index;
    if(isInteger) {
        try {
            index = hashInteger(std::stoi(value));
        } catch(...) {
            return -1;
        }
    } else {
        index = hashString(value);
    }
    
    int originalIndex = index;
    
    while(!table[index].empty()) {
        if(table[index] == value) {
            return index;
        }
        index = (index + 1) % TABLE_SIZE;
        if(index == originalIndex) {
            break;
        }
    }
    return -1;
}

void Hash::display() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        std::cout << i << ": " << (table[i].empty() ? "---" : table[i]) << "\n";
    }
}