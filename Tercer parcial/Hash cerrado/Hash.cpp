#include "Hash.h"
#include <iostream>
#include <bitset>

Hash::Hash() : table(TABLE_SIZE), isInteger(true), useQuadraticProbing(false), doubleHashing(false) {}

void Hash::setHashType(bool useInteger) {
    isInteger = useInteger;
    table = std::vector<std::string>(TABLE_SIZE); // Reinicia la tabla
}

void Hash::setProbingMethod(bool useQuadratic) {
    useQuadraticProbing = useQuadratic;
}

void Hash::setDoubleHashing(bool useDoubleHashing) {
    doubleHashing = useDoubleHashing;
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

int Hash::doubleHashString(const std::string& str) {
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
    return hash;
}

int Hash::hash2(int value) {
    return( 7 - (value % 7)); // Hash secundario
}

int Hash::probe(int index, int attempt, int hash1) {
    if (useQuadraticProbing) {
        return (index + attempt * attempt) % TABLE_SIZE;
    }

    if (doubleHashing) {
        return (index + attempt*  (hash2(hash1)%7)) % TABLE_SIZE;
    }

    return (index + attempt) % TABLE_SIZE; // Linear Probing por defecto
}

bool Hash::insert(const std::string& value) {
    int index = isInteger ? hashInteger(std::stoi(value)) : hashString(value);
    int attempt = 0;
    int originalIndex = index;
    int hash1 = 0;
    if(doubleHashing) {
        hash1 = doubleHashString(value);
    }

    while (!table[index].empty()) {
        attempt++;
        index = probe(originalIndex, attempt, hash1);
        if (index == originalIndex) {
            std::cout << "Tabla llena\n";
            return false;
        }
    }
    
    table[index] = value;
    return true;
}

int Hash::findPosition(const std::string& value) {
    int index = isInteger ? hashInteger(std::stoi(value)) : hashString(value);
    int attempt = 0;
    int originalIndex = index;
    int hash1 = 0;
    if(doubleHashing) {
        hash1 = doubleHashString(value);
    }
    
    while (!table[index].empty()) {
        if (table[index] == value) {
            return index;
        }
        attempt++;
        index = probe(originalIndex, attempt, hash1);
        if (index == originalIndex) {
            break;
        }
    }
    return -1;
}

void Hash::display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        std::cout << i << ": " << (table[i].empty() ? "---" : table[i]) << "\n";
    }
}
